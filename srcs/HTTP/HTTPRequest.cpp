#include "HTTPRequst.hpp"

namespace ft {
    HTTPRequest::HTTPRequest() : _responseCode(), _parseStatus(requestLine), _requestMethod(), _requestURI(), _HTTPv(), _headerFields(), _currentHeader(),
        _contentLength(), _readBytes(0), _body(), _save() {
            _validMethods.push_back("POST");
            _validMethods.push_back("GET");
            _validMethods.push_back("DELETE");
        }

    HTTPRequest::~HTTPRequest(){}

    int      HTTPRequest::Parse(const std::string& request) {
        // if _request.empty() && !_readBytes.... && _parseStatus >headerfields??.... && !conetntlenth && !transferencoding??
        //, throw error? means body is too big

        _save += request;

        if (_parseStatus == requestLine) {
            _parseRequestLine();
        } 
        if (_parseStatus == headerFields) {
            bool finished = _parseHeaderFields();
            if (finished) {
                if (_headerFields.size() > MAXHEADERS || _headerFields.find("host") == _headerFields.end()) {
                    _throw(400, "Bad Request");
                }
                _decideReadType();
            }
        }

        if (_parseStatus == readChunks) {
            size_t i = 0;
            while (_save.find(DELIM) != std::string::npos) {
                if (!_readBytes) {
                    i = _save.find(DELIM);
                    _readBytes = _strToBase(_save.substr(0, i), std::hex);
                    _save.erase(0, i + DELIM.size());
                    if (_readBytes == 0) {
                        _responseCode = 200;
                        _parseStatus = complete;
                        break ;
                    }
                    // if never recieve 0??
                }
                if (_save.find(DELIM) == std::string::npos) {
                    break ;
                }
                i = _save.find(DELIM);
                std::string line = _save.substr(0, i);
                _save.erase(0, i + DELIM.size());
                if (_readBytes != line.size()) {
                    // throw error
                }
                _body += line;
                _readBytes = 0;
            }
            // check for trailer header field when recieve 0 size
        } else if (_parseStatus == readStraight) {
            _readBody();
        }

        //if (!_readBytes && _parseStatus != complete && )
        return (HTTPRequestComplete() ? 0 : 1);
    }

    const std::string&                  HTTPRequest::GetRequestMethod() { return _requestMethod; }
    const std::string&                  HTTPRequest::GetRequestURI() { return _requestURI; }
    const HTTPRequest::header_type&     HTTPRequest::GetHeaderFields() { return _headerFields; }
    const std::string&                  HTTPRequest::GetBody() { return _body; }

    void     HTTPRequest::_parseRequestLine() {
        size_t i;
        
        if (_requestMethod == "") {
            i = _save.find(SP);
            if (i != std::string::npos) {
                _requestMethod = _save.substr(0, i);
                _save.erase(0, i + SP.size());
                if (std::find(_validMethods.begin(), _validMethods.end(), _requestMethod) == _validMethods.end()) {
                    _throw(501, "Not Implemented");
                }
            }  
        }
        if (_requestURI == "") {
            i = _save.find(SP);
            if (i != std::string::npos) {
                _requestURI = _save.substr(0, i);
                _save.erase(0, i + SP.size()); 
                if (_requestURI == "*") { // REMOVE IF DO OPTIONS METHOD
                    _throw (400, "Bad request");
                }
                if (_requestURI.size() > MAXBUFFER) {
                    _throw (414, "URI Too Long");
                }
            }
        }
        if (_HTTPv == "") {
            i = _save.find(DELIM);
            if (i != std::string::npos) {
                if (_requestMethod == "" || _requestURI == "") {
                    _throw(400, "Bad Request");
                }
                const std::string versionComp = "HTTP/1.";
                _HTTPv = _save.substr(0, i);
                _save.erase(0, i + DELIM.size());
                _parseStatus = headerFields;
                if (_HTTPv.size() != HTTPV.size() || _HTTPv.compare(0, versionComp.size(), versionComp) != 0 || !isdigit(_HTTPv[_HTTPv.size() - 1])) {
                    _throw(505, "HTTP Version Not Supported");
                }
            } 
        }    
    }

    bool    HTTPRequest::_parseHeaderFields() {
        std::locale loc;
        while (_save.find(DELIM) != 0 && _save.find(DELIM) != std::string::npos) {
            if (_currentHeader.first == "") {
                size_t i = _save.find(CN);
                if (i != std::string::npos) {
                    _currentHeader.first = _save.substr(0, i); 
                    for (size_t i = 0; i < _currentHeader.first.length(); ++i) {
                        _currentHeader.first[i] = std::tolower(_currentHeader.first[i], loc);
                    } 
                    _save.erase(0, i + CN.size());
                }
            }
            if (_currentHeader.first != "") {
                size_t i = _save.find(DELIM);
                if (i != std::string::npos) {
                    // obs-fold MUST either reject the message by 400 bad request, preferably with representation explaining that obsolete line folding is uacceptable
                    // or reaplce each received obs-fold with one or more space octets prior to interpreting the field value or forwardingin the message downstream
                    _currentHeader.second = _save.substr(0, i);
                    _save.erase(0, i + DELIM.size());
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
                    if (_currentHeader.first[_currentHeader.first.size() - 1] == ' ') {
                        while (_currentHeader.first[_currentHeader.first.size() - 1] == ' ') {
                            _currentHeader.first.erase(_currentHeader.first.size() - 1, 1);
                        }
                        _headerFields.insert(std::make_pair(_currentHeader.first, _currentHeader.second));
                        _throw(400, "Bad Request");
                    }
                    _headerFields.insert(std::make_pair(_currentHeader.first, _currentHeader.second));
                    std::cout << _currentHeader.first << ':' << _currentHeader.second << std::endl;
                    _currentHeader.first = "";
                    _currentHeader.second = "";
                }
            }
        } 
        if (_save.find(DELIM) == 0) {
            _save.erase(0, DELIM.size()); 
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
            _throw(400, "Bad Request");
        } 
        if (!_readBytes) {
            _responseCode = 200;
            _parseStatus = complete;
        }
    }

    bool    HTTPRequest::HTTPRequestComplete() {
        return (_parseStatus == complete);
    }

    void    HTTPRequest::_decideReadType() {
        header_type::iterator transfer_encoding = _headerFields.find("transfer-encoding");
        header_type::iterator content_length = _headerFields.find("content-length");

        if (transfer_encoding != _headerFields.end() && content_length != _headerFields.end()) {
            _headerFields.erase(content_length); 
            _throw(400, "Bad Request");
        } else if (transfer_encoding != _headerFields.end()) {
            const std::string te = transfer_encoding->second;
            const std::string chunked = "chunked";
            if (te.size() < chunked.size() || te.compare(te.length() - chunked.size(), chunked.size(), chunked) != 0) {
                _throw(400, "Bad Request");
            }
            // A server that receives a request message with a transfer coding it does not understand SHOOULD respond with 501 (Not Implemented)
            // if request methos == GET throw 400? if reqeust method == DELETE throw 405 "not allowed"?
            _parseStatus = readChunks;
        } else if (content_length!= _headerFields.end()) { 
            // if request methos == GET throw? if reqeust method == DELETE throw 405 "not allowed"?
            _parseStatus = readStraight;
        } else {
            _responseCode = 200;
            _parseStatus = complete;
        }
    }

    unsigned int     HTTPRequest::_strToBase(const std::string& str, std::ios_base& (*base)(std::ios_base&)) {
        std::stringstream  stream(str);
        unsigned long int  num;

        stream >> base >> num;

        if (num > std::numeric_limits<unsigned int>::max()) {
            _throw(400, "Bad Request");
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
}
