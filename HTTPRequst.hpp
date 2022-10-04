#pragma once
#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <string>
#include <cstddef>

class HTTPRequest {
public:
    typdef std::vector<std::pair<std::string, std::string> >   header_type;

private:
    std::string     _requestMethod;
    std::string     _requestURI;
    header_type     _headerFields;
    std::string     _body;

public:
    HTTPRequest(){}
    ~HTTPRequest(){}

    void ParseHTTPRequest(const std::string& request);

    const std::string&  GetRequestMethod();
    const std::string&  GetRequestURI();
    const header_type&  GetHeaderFields();
    const std::string&  GetBody();

private:

    void    _parseStartLine(const std::string& request);
    void    _parseHeaderFields(const std::stringstream& ss, const std::string& request);

};

#endif
