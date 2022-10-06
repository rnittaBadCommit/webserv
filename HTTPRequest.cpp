#include "HTTPRequst.hpp"

#include <iostream>
HTTPRequest::HTTPRequest() : _requestMethod(), _requestURI(), _HTTPv(), _headerFields(), _headerFieldsFin(false), _body(), _save() {}
HTTPRequest::~HTTPRequest(){}

int      HTTPRequest::Parse(const std::string& request) {
    // Need to handle request line??

    int     rlt = 1;
    _save += request;

    //rlt 0 = fin, 1 = not fin, 2 = empty string

    if (_requestMethod == "") {
        rlt = _parseRequestMethod();
    }
    if (rlt && _requestURI == "") {
       rlt =  _parseRequestURI();
    }
    if (rlt && _HTTPv == "") {
        rlt = _parseHTTPv();
    }
    if (rlt && !_headerFieldsFin){
       //return _parseHeaderFields();
    }

    // if content-length
    //    ...

    //getbody
    return (1);
}

const std::string&                  HTTPRequest::GetRequestMethod() { return _requestMethod; }
const std::string&                  HTTPRequest::GetRequestURI() { return _requestURI; }
const HTTPRequest::header_type&     HTTPRequest::GetHeaderFields() { return _headerFields; }
const std::string&                  HTTPRequest::GetBody() { return _body; }

int     HTTPRequest::_parseRequestMethod() {
    size_t i = _save.find_first_of(' ');

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
    size_t i = _save.find('\r\n');

    if (i != std::string::npos) {
        _HTTPv = _save.substr(0, i);
        // if _requesturi not HTTP/1.1 error?
        _save.erase(0, i + 1);
        //return (_parseHeaderFields());
    }
    return (1);
}
