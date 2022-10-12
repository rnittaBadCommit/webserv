#include "HTTPRequst.hpp"
#include "webserv.hpp"
#include <iostream>

HTTPRequest::HTTPRequest() : _responseCode(), _parseStatus(requestLine), _requestMethod(), _requestURI(), _HTTPv(), _headerFields(), _currentHeader(),
    _contentLength(), _readBytes(0), _body(), _save(), _reqLineHeader() {}

HTTPRequest::~HTTPRequest(){}

int      HTTPRequest::Parse(const std::string& request) {
    // if _request.empty() && !_readBytes.... && _parseStatus >headerfields??.... && !conetntlenth && !transferencoding??
    //, throw error? means body is too big

    _save += request;
    if (_parseStatus < readChunks) {
        _reqLineHeader += request;
    }

    if (_parseStatus == requestLine) {
        _parseRequestLine();
        // check for errors to return 0
    } 
    if (_parseStatus == headerFields) {
        bool finished = _parseHeaderFields();
        if (finished) {
            _decideReadType();
        }
        // check for errors to return 0
    }

    if (_parseStatus == readChunks) {

    } else if (_parseStatus == readStraight) {
        _readBody();
    }

    if (HTTPRequestComplete()) {
        return (0);
    }
    return (1);
}

const std::string&                  HTTPRequest::GetRequestMethod() { return _requestMethod; }
const std::string&                  HTTPRequest::GetRequestURI() { return _requestURI; }
const HTTPRequest::header_type&     HTTPRequest::GetHeaderFields() { return _headerFields; }
const std::string&                  HTTPRequest::GetBody() { return _body; }
const std::string&                  HTTPRequest::GetReqLineHeader() { return _reqLineHeader; }

void     HTTPRequest::_parseRequestLine() {
    // recommended to receive  minimum of 8000 octets in request line
    // For invalid request-line either respond 404 (bad request) or 301 (moved permanently)
    size_t i;
    
    if (_requestMethod == "") {
        // for method longer than server implements, response code 501 (not implemented)
        i = _save.find(' ');
        if (i != std::string::npos) {
            _requestMethod = _save.substr(0, i);
            _save.erase(0, i + 1);
        }  
    }
    if (_requestURI == "") {
        // for URI longer than server wishes to request response code 414 (uri too long)
        i = _save.find(' ');
        if (i != std::string::npos) {
            _requestURI = _save.substr(0, i);
            _save.erase(0, i + 1); 
        }
    }
    if (_HTTPv == "") {
        // if _requesturi not HTTP/1.1 error?
        i = _save.find(DELIM);
        if (i != std::string::npos) {
            _HTTPv = _save.substr(0, i);
            _save.erase(0, i + 1);
            _parseStatus = headerFields;
        } 
    }    
}

bool    HTTPRequest::_parseHeaderFields() {
    std::locale loc;
    while (_save.find(DELIM) != 0 && _save.find(DELIM) != std::string::npos) {
        // response code for too many headers? (avoid smuggling etc)
        if (_currentHeader.first == "") {
            size_t i = _save.find(':');
            if (i != std::string::npos) {
                // Any message that ocntains a white space between a header field-name and colon MUST reject
                // the recieved request with response code of 400 (Bad Request)
                // and proxy MUST remove any such whitespace froma resopnse message before forwarding the message downstream
                _currentHeader.first = _save.substr(0, i);
                for (size_t i = 0; i < _currentHeader.first.length(); ++i) {
                    _currentHeader.first[i] = std::tolower(_currentHeader.first[i], loc);
                }
                _save.erase(0, i + 1);
            }
        }
        if (_currentHeader.first != "") {
            size_t i = _save.find(DELIM);
            if (i != std::string::npos) {
                // obs-fold MUST either reject the message by 400 bad request, preferably with representation explaining that obsolete line folding is uacceptable
                // or reaplce each received obs-fold with one or more space octets prior to interpreting the field value or forwardingin the message downstream
                _currentHeader.second = _save.substr(0, i);
                _save.erase(0, i + 1);
                // also need to remove trailing white spaces
                while (_currentHeader.second.size() && isspace(_currentHeader.second[0])) {
                    _currentHeader.second.erase(0, 1);
                }
                for (size_t i = 0; i < _currentHeader.second.length(); ++i) {
                    _currentHeader.second[i] = std::tolower(_currentHeader.second[i], loc);
                }
                if (_currentHeader.first == "content-length") {
                    // multiple content-length headers with same number? don't change _contentLength / (add , to _fieldheader content length header?)
                    // multiple with differing numbers or a single invalid value is unrecoverable error.. 400 (bad request)
                    _contentLength = _strToBase(_currentHeader.second, std::dec);
                    _readBytes = _contentLength;
                }
                _headerFields.insert(std::make_pair(_currentHeader.first, _currentHeader.second));
                _currentHeader.first = "";
                _currentHeader.second = "";
            }
        }
    }
    if (_save.find(DELIM) == 0) {
        _save.erase(0, 1); 
        return (true);
    } 
    return (false);
}

void    HTTPRequest::_readBody() {
    if (_readBytes >= _save.size()) {
        _readBytes -= _save.size();
        _body += _save;
        _save.clear();
    } else if (_parseStatus == readChunks) {
        _body += _save.substr(0, _readBytes);
        _save.erase(0, _readBytes);
        _readBytes = 0;
        // return for outside loop to get new readbytes and enter again?
        // what if bytes to be read doesn't match.. to big / too little
    } else {
        _body += _save.substr(0, _readBytes);
        _save.erase(0, _readBytes);
        _readBytes = 0;
        _throw(413, "Payload too Large");
    } 
    if (!_readBytes) {
        _parseStatus = complete;
    }
}

bool    HTTPRequest::HTTPRequestComplete() {
    return (_parseStatus == complete);
}

void    HTTPRequest::_decideReadType() {
    // HEAD, 2xx (successful) response to CONNECT, 1xx (Informatinoal), 204 (No Content), and 304 (Not Modified) will not include body
    header_type::iterator transfer_encoding = _headerFields.find("transfer-encoding");
    header_type::iterator content_length = _headerFields.find("content-length");

    if (transfer_encoding != _headerFields.end() && content_length != _headerFields.end()) {
        //RFC 7230:3.3.2 #3 should be handled as an error, but also must remove content_length before forwarding such a message downstream.
        _headerFields.erase(content_length); 
        // set error response code
    } else if (transfer_encoding != _headerFields.end()) {
        // A server that receives a request message with a transfer coding it does not understand SHOOULD respond with 501 (Not Implemented)
        // if 'chunked' is not the final encoding, the body length cannot be determined reliably, the server MUST respond with 400 (Bad Request)
        // and then close the connection
        _parseStatus = readChunks;
    } else if (content_length!= _headerFields.end()) { 
        //RFC 2068:4.4 must notify if too many or too few bytes are recieved
        // If the sender coses teh connection or the recipient times out before the indicated number of octets are 
        // received, the recipient MUST consider the message to be incomplete and close the connection
        _parseStatus = readStraight;
    } else {
        // MESSAGE BODY LENGTH SHOULD BE ZERO
        // A server MAY reject a request that contains a message body but not a content-length by responding with 411 (Length Required)
        // if request.lengt() == 0 (no body??), return 0 else below?
        //RFC 2161:4.3 ignore the body? but per below must notify
        // Not sure yet  
        // does it mean only a head request, etc? set status to complete
        if (_save.size()) {
            _throw(411, "Length Required");
        }
        _responseCode = 200; //??
        _parseStatus = complete;
    }
}

unsigned int     HTTPRequest::_strToBase(const std::string& str, std::ios_base& (*base)(std::ios_base&)) {
    std::stringstream  stream(str);
    unsigned long int  num;

    stream >> base >> num;

    if (num > std::numeric_limits<unsigned int>::max()) {
        //RFC 2068:4.4 maybe response code 411
        //RFC 7231:6.5.11 response code 413 payload too large
        //RFC 7230:3.3.3 #4 response code 400 (bad request) for when content-length value is invalid
        throw std::runtime_error("overflow/underflow");
    }
    return (static_cast<unsigned int>(num));
}
void    HTTPRequest::_throw(int responseCode, const std::string& message) {
    _responseCode = responseCode;
    throw std::runtime_error(message);
}

void    HTTPRequest::PrintRequest() {
    std::cout << _requestMethod << ' ' << _requestURI << ' ' << _HTTPv << std::endl;
    for(header_type::iterator it = _headerFields.begin(); it != _headerFields.end(); ++it) {
        std::cout << it->first << ":" << it->second << std::endl;
    }
}

void    HTTPRequest::PrintBody() {
    std::cout << _body << std::endl;
}