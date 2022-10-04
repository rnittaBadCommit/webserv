#include "HTTPRequst.hpp"

HTTPRequest::HTTPRequest(){}
HTTPRequest::~HTTPRequest(){}

void                HTTPRequest::ParseHTTPRequest(const std::string& request) {

}

const std::string&  HTTPRequest::GetRequestMethod() { return RequestMethod; }
const std::string&  HTTPRequest::GetRequestURI() { return RequestURI; }
const header_type&  HTTPRequest::GetHeaders() { return Headers; }
const std::string&  HTTPRequest::GetBody() { return Body; }