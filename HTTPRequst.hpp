#pragma once
#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <string>
#include <cstddef>
#include <vector>
#include <map>

class HTTPRequest {
public:
    typedef std::vector<std::map<std::string, std::string> >   header_type;

private:
    std::string     _requestMethod;
    std::string     _requestURI;
    std::string     _HTTPv;
    header_type     _headerFields;
    bool            _headerFieldsFin;
    std::string     _body;
    std::string     _save;

public:
    HTTPRequest();
    ~HTTPRequest();

    int Parse(const std::string& request);

    const std::string&  GetRequestMethod();
    const std::string&  GetRequestURI();
    const std::string&  GetHTTPv();
    const header_type&  GetHeaderFields();
    const std::string&  GetBody();

private:

    int     _parseRequestMethod();
    int     _parseRequestURI();
    int     _parseHTTPv();
    //int     _parseHeaderFields();

};

#endif
