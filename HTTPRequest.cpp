#include "HTTPRequst.hpp"
#include "webserv.hpp"
#include <iostream>

HTTPRequest::HTTPRequest() : _requestMethod(), _requestURI(), _HTTPv(), _headerFields(), _currentHeader(),
    _contentLength(), _headerFieldsFin(false), _body(), _save() {}
HTTPRequest::~HTTPRequest(){}

int      HTTPRequest::Parse(const std::string& request) {
    // Need to handle request line??

    int     rlt = 1;
    _save += request;

    //rlt 0 = empty string, 1 = not empty

    if (_requestMethod == "") {
        rlt = _parseRequestMethod();
    }
    if (rlt && _requestURI == "") {
       rlt =  _parseRequestURI();
    }
    if (rlt && _HTTPv == "") {
        rlt = _parseHTTPv();
    }
    if (rlt && _HTTPv != "" && !_headerFieldsFin) {
        _parseHeaderFields();
    }
    if (_headerFieldsFin) {
        header_type::iterator content_length = _headerFields.find("content-length");
        header_type::iterator field_content = _headerFields.find("field-content");
        if (content_length != _headerFields.end() && field_content != _headerFields.end()) {
            throw std::runtime_error("HTTP reques should not contain both content-length and field-content");
        } else if (content_length != _headerFields.end() && field_content != _headerFields.end()) {
            // Not sure yet
        } else if (content_length != _headerFields.end()) {
            std::cout << "we're gonne read: " << _contentLength << " bytes to get the body" << std::endl;
        } else {
            std::cout << "we're gonna read some chunks until we get a 0 size chunk.. whatever that means...." << std::endl;
        }
        return (0);
    }

    if (_HTTPRequestComplete()) {
        return (0);
    }
    return (1);
}

const std::string&                  HTTPRequest::GetRequestMethod() { return _requestMethod; }
const std::string&                  HTTPRequest::GetRequestURI() { return _requestURI; }
const HTTPRequest::header_type&     HTTPRequest::GetHeaderFields() { return _headerFields; }
const std::string&                  HTTPRequest::GetBody() { return _body; }

int     HTTPRequest::_parseRequestMethod() {
    size_t i = _save.find(' ');

    if (i != std::string::npos) {
        _requestMethod = _save.substr(0, i);
        _save.erase(0, i + 1);
        return(1);
    }
    return (0);
}

int     HTTPRequest::_parseRequestURI() {
    size_t i = _save.find(' ');

    if (i != std::string::npos) {
        _requestURI = _save.substr(0, i);
        _save.erase(0, i + 1);
        return (1);
    }
    return (0);
}

int     HTTPRequest::_parseHTTPv() {
    size_t i = _save.find(DELIM);

    if (i != std::string::npos) {
        _HTTPv = _save.substr(0, i);
        // if _requesturi not HTTP/1.1 error?
        _save.erase(0, i + 1);
        //return (_parseHeaderFields());
        return (1);
    }
    return (0);
}

void    HTTPRequest::_parseHeaderFields() {
    std::locale loc;
    while (_save.find(DELIM) != 0 && _save.find(DELIM) != std::string::npos) {
        if (_currentHeader.first == "") {
            size_t i = _save.find(':');
            if (i != std::string::npos) {
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
                _currentHeader.second = _save.substr(0, i);
                _save.erase(0, i + 1);
                while (_currentHeader.second.size() && isspace(_currentHeader.second[0])) {
                    _currentHeader.second.erase(0, 1);
                }
                for (size_t i = 0; i < _currentHeader.second.length(); ++i) {
                    _currentHeader.second[i] = std::tolower(_currentHeader.second[i], loc);
                }
                if (_currentHeader.first == "content-length") {
                    _contentLength = _strToBase(_currentHeader.second, std::dec);
                }
                _headerFields.insert(std::make_pair(_currentHeader.first, _currentHeader.second));
                _currentHeader.first = "";
                _currentHeader.second = "";
            }
        }
    }
    if (_save.find(DELIM) == 0) {
        _headerFieldsFin = true;
    } 
}

bool    HTTPRequest::_HTTPRequestComplete() {
    if (_contentLength && _body == "") {
        return (false);
    }
    return (_requestMethod != "" && _requestURI != "" && _HTTPv != "" && _headerFieldsFin);
}

void    HTTPRequest::PrintRequest() {
    std::cout << _requestMethod << ' ' << _requestURI << ' ' << _HTTPv << std::endl;
    for(header_type::iterator it = _headerFields.begin(); it != _headerFields.end(); ++it) {
        std::cout << it->first << ":" << it->second << std::endl;
    }
}

unsigned int     HTTPRequest::_strToBase(const std::string& str, std::ios_base& (*base)(std::ios_base&)) {
    std::stringstream  stream(str);
    unsigned long int  num;

    stream >> base >> num;

    if (num > std::numeric_limits<unsigned int>::max()) {
        throw std::runtime_error("overflow/underflow");
    }
    return (static_cast<unsigned int>(num));
}