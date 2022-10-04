#include "HTTPRequst.hpp"

HTTPRequest::HTTPRequest(){}
HTTPRequest::~HTTPRequest(){}

void                HTTPRequest::ParseHTTPRequest(const std::string& request) {
    // Need to handle request line??
    std::stringstream   ss(reqeust);
    std::string rqst = std::getline(ss, rqst, '\n');

    _parseStartLine(rqst);
    while (std::getline(ss, rqst, '\n')) {
        _parseHeaderFields(ss, rqst);
    }
    // if !content-length
    //    retrn
    // else
    //    getbody
}

const std::string&  HTTPRequest::GetRequestMethod() { return _requestMethod; }
const std::string&  HTTPRequest::GetRequestURI() { return _requestURI; }
const header_type&  HTTPRequest::GetHeaderFields() { return _headerFields; }
const std::string&  HTTPRequest::GetBody() { return _body; }

size_t  HTTPRequest::_parseStartLine(const std::string& request) {
    size_t  = 0;

    // get Request Method
    i = request.find_first_of(' ');
    if (i != std::string::npos) {
        _requestMethod = request.substr(0, i);
    } else {;}//Throw exception?なんかエラーハンドル
    start = i + 1;

    // get request-URI
    i = request.find_last_of(' ');
    if (i != std::string::npos) {
        _requestURI = request.substr(start, i - start);
    } else {;}//Throw exception?なんかエラーハンドル
    start = i + 1;

    i = request.find('\n');
    if (request.substr(start, i - start) != "HTTP/1.1"
        || !_requestMethod || !_requestURI) {
           ;//Throw exception?なんかエラーハンドル
    }
}

void    _parseHeaderFields(const std::stringstream& ss, const std::string& request) {
    while (std::getline(ss, rqst, '\n') /*!= linebreak*/) {
        // parse eacher header
    }
}