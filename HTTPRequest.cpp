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
    if (rlt && !_headerFieldsFin) {
        _parseHeaderFields();
    }

    // if content-length
    //    ...

    //getbody
    return (rlt);
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
    }
    return (1);
}

int     HTTPRequest::_parseRequestURI() {
    size_t i = _save.find(' ');

    if (i != std::string::npos) {
        _requestURI = _save.substr(0, i);
        _save.erase(0, i + 1);
    }
    return (1);
}

int     HTTPRequest::_parseHTTPv() {
    size_t i = _save.find(DELIM);

    if (i != std::string::npos) {
        _HTTPv = _save.substr(0, i);
        // if _requesturi not HTTP/1.1 error?
        _save.erase(0, i + 1);
        //return (_parseHeaderFields());
    }
    return (1);
}

int     HTTPRequest::_parseHeaderFields() {
    std::locale loc;
    if (_currentHeader.first == "") {
        size_t i = _save.find(':');
        if (i != std::string::npos) {
            _currentHeader.first = _save.substr(0, i);
            for (size_t i = 0; i < _currentHeader.first.length(); ++i) {
                    std::tolower(_currentHeader.first[i], loc);
            }
            _save.erase(0, i + 1);
        }
    }
    if (_currentHeader.first != "") {
        size_t i = _save.find(DELIM);
        if (i != std::string::npos) {
            _currentHeader.second = _save.substr(0, i);
            _save.erase(0, i + 1);
            /*while (_currentHeader.second.size() && isspace(_currentHeader.second.front())) {
                _currentHeader.second.erase(0);
            }
            for (size_t i = 0; i < _currentHeader.second.length(); ++i) {
                std::tolower(_currentHeader.second[i], loc);
            }*/
            if (_currentHeader.first == "content-length") {
                //_contentLength = stoi _currentHeader.second;
            }
            _headerFields.insert(std::make_pair(_currentHeader.first, _currentHeader.second));
            _currentHeader.first = "";
            _currentHeader.second = "";
        }
    }

    return (1);
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
        std::cout << it->first << ": " << it->second << std::endl;
    }
}
