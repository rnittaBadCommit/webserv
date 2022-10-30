#include "HTTPHead.hpp"

namespace ft {
    HTTPHead::HTTPHead() : _responseCode(), _parseStatus(requestLine),
        _requestMethod(), _requestURI(), _HTTPv(), _headerFields(), _currentHeader(), _save() {}

    HTTPHead::HTTPHead(const HTTPHead& src) {
        _responseCode = src._responseCode;
        _parseStatus = src._parseStatus;
        _requestMethod = src._requestMethod;
        _requestURI = src._requestURI;
        _HTTPv = src._HTTPv;
        _headerFields = src._headerFields;
        _currentHeader = src._currentHeader; 
        _save = src._save;
    }
    HTTPHead& HTTPHead::operator=(const HTTPHead& rhs) {
        if (this != &rhs) {
            _responseCode = rhs._responseCode;
            _parseStatus = rhs._parseStatus;
            std::cout << "before rmethod\n";
            std::cout << "rhs: " << rhs._requestMethod << std::endl;
            _requestURI = rhs._requestURI;
            _requestMethod = rhs._requestMethod;
            std::cout << "after rmethod\n";

            _HTTPv = rhs._HTTPv;
            _headerFields = rhs._headerFields;
            _currentHeader = rhs._currentHeader; 
            _save = rhs._save;
        }
        return (*this);
    }

    HTTPHead::~HTTPHead(){}

    int      HTTPHead::Parse(const std::string& request) {
        _save += request;

        if (_parseStatus == requestLine) {
            parseRequestLine();
        } 
        if (_parseStatus == headerFields) {
            parseHeaderFields();
            if (_parseStatus > headerFields) {
                if (_headerFields.size() > MAXHEADERS || _headerFields.find("host") == _headerFields.end()) {
                    _throw(400, "Bad Request - MAXHEADERS / host");
                }
            }
        }
        return (_parseStatus > headerFields ? 0 : 1);
    }

    const std::string              HTTPHead::GetHost() const {
        header_type::const_iterator host = _headerFields.find("host");
        return (host == _headerFields.end() ? "" : host->second);
    }
    const int&                      HTTPHead::GetResponseCode() const { return _responseCode;}
    const HTTPParseStatus&          HTTPHead::GetParseStatus() const { return _parseStatus; }
    const std::string&              HTTPHead::GetRequestMethod() const { return _requestMethod; }
    std::string&                    HTTPHead::GetRequestURI() { return _requestURI; }
    const std::string&              HTTPHead::GetHTTPv() const { return _HTTPv; }
    HTTPHead::header_type&          HTTPHead::GetHeaderFields() { return _headerFields; }
    const std::string&              HTTPHead::getSave() const { return _save; }

    void     HTTPHead::parseRequestLine() {
        size_t i;
        
        if (_requestMethod == "") {
            i = _save.find(SP);
            if (i != std::string::npos) {
                _requestMethod = _save.substr(0, i);
                _save.erase(0, i + SP.size());
            }  
        }
        if (_requestURI == "") {
            i = _save.find(SP);
            if (i != std::string::npos) {
                _requestURI = _save.substr(0, i);
                _save.erase(0, i + SP.size()); 
                if (_requestURI.size() > MAXBUFFER) {
                    _throw (414, "URI Too Long");
                }
            }
        }
        if (_HTTPv == "") {
            i = _save.find(DELIM);
            if (i != std::string::npos) {
                if (_requestMethod == "" || _requestURI == "") {
                    _throw(400, "Bad Request - invalid request line");
                }
                const std::string versionComp = "HTTP/1.";
                _HTTPv = _save.substr(0, i);
                _save.erase(0, i + DELIM.size());
                std::cerr << "CHANGING STATUS\n";
                _parseStatus = headerFields;
                if (_HTTPv.size() != HTTPV.size() || _HTTPv.compare(0, versionComp.size(), versionComp) != 0 || !isdigit(_HTTPv[_HTTPv.size() - 1])) {
                    _throw(505, "HTTP Version Not Supported");
                }
            } 
        }    
    }

    void    HTTPHead::parseHeaderFields() {
        while (_save.find(DELIM) != 0 && _save.find(DELIM) != std::string::npos) {
            // get header key
            if (_currentHeader.first == "") {
                size_t i = _save.find(CN);
                if (i != std::string::npos) {
                    _currentHeader.first = _save.substr(0, i); 
                    toLower(_currentHeader.first); 
                    _save.erase(0, i + CN.size());
                }
            }
            // get header value and validate header
            if (_currentHeader.first != "") {
                size_t i = _save.find(DELIM);
                if (i != std::string::npos) {
                    _currentHeader.second = _save.substr(0, i);
                    _save.erase(0, i + DELIM.size());
                    TrimWSP(_currentHeader.second);
                    toLower(_currentHeader.second);
                    if (!multiInclusion()) {
                        _headerFields.insert(std::make_pair(_currentHeader.first, _currentHeader.second));
                    }
                    _currentHeader.first.clear();
                    _currentHeader.second.clear();
                }
            }
        }
        // decide if header is complete (line break reached because \r\n is the first character)
        if (_save.find(DELIM) == 0) {

            _save.erase(0, DELIM.size()); 
            _parseStatus = complete;
        }
    }

    void    HTTPHead::ParseRequestURI(){
        if (_requestURI[0] == '/') {
            return ;
        }

        std::string http = "http://";
        std::string host;

        // GET scheme and remove
        size_t i = _requestURI.find(http);
        if (i == std::string::npos) {
            _throw(400, "Bad Request - unrecognize URL scheme");
        }
        _requestURI.erase(0, http.size());

        // split authority (host) and path
        i = _requestURI.find('/');
        if (i == 0) {
            _throw(400, "Bad Request - no host provided in URI");
        }
        if (i == std::string::npos) { // no '/' exists 
            host = _requestURI;
            _requestURI.clear();
        } else {
            host = _requestURI.substr(0, i);
            _requestURI.erase(0, i);
        }

        // check for user info
        if (host.find('@') != std::string::npos) {
            _throw(400, "Bad Request - this server does not handle user info in URI");
        }
        // remove port info if it exists
        if ((i = host.find(':')) != std::string::npos) {
            host.erase(i);
        }

        // set host
        _headerFields["host"] = host;        
    }

    void        HTTPHead::toLower(std::string& str) {
        std::locale loc;
        for (size_t i = 0; i < str.length(); ++i) {
            str[i] = std::tolower(str[i], loc);
        } 
    }

    bool    HTTPHead::multiInclusion() {

        header_type::iterator _findHeader = _headerFields.find(_currentHeader.first);

        if (_findHeader != _headerFields.end()) {
            _headerFields[_currentHeader.first] = _findHeader->second + ", " + _currentHeader.second;
            return (true);
        }
        return (false);
    } 

    void    HTTPHead::_throw(int responseCode, const std::string& message) {
        _responseCode = responseCode;
        throw std::runtime_error(message);
    }

    void    HTTPHead::PrintRequest() {
        std::cout << _requestMethod << ' ' << _requestURI << ' ' << _HTTPv << std::endl;
        for(header_type::iterator it = _headerFields.begin(); it != _headerFields.end(); ++it) {
            std::cout << it->first << ":" << it->second << std::endl;
        }
    }
}
