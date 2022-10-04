#pragma once
#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <string>

class HTTPRequest {
public:
    typdef std::vector<std::pair<std::string, std::string> >   header_type;

private:
    std::string     RequestMethod;
    std::string     RequestURI;
    header_type     Headers;
    std::string     Body;

public:
    HTTPRequest(){}
    ~HTTPRequest(){}

    void ParseHTTPRequest(const std::string& request);
    const std::string&  GetRequestMethod();
    const std::string&  GetRequestURI();
    const header_type&  GetHeaders();
    const std::string&  GetBody();

};

#endif
