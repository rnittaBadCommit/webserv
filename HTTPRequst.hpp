#pragma once
#ifndef HTTPREQUEST_HPP
# define HTTPREQUEST_HPP

#include <string>
#include <limits>
#include <cstddef>
#include <vector>
#include <map>
#include <sstream>

class HTTPRequest {
public:
    typedef std::map<std::string, std::string>  header_type;
    typedef std::pair<std::string, std::string> header_value;

private:
    std::string    _requestMethod;
    std::string    _requestURI;
    std::string    _HTTPv;
    header_type    _headerFields;
    header_value   _currentHeader;
    unsigned int   _contentLength;
    bool           _headerFieldsFin;
    std::string    _body;
    std::string    _save;
    int            _errorStatus;

public:
    HTTPRequest();
    ~HTTPRequest();

    int     Parse(const std::string& request);
    void    PrintRequest();

 
    const std::string&  GetRequestMethod();
    const std::string&  GetRequestURI();
    const std::string&  GetHTTPv();
    const header_type&  GetHeaderFields();
    const std::string&  GetBody();

private:

    int     _parseRequestMethod();
    int     _parseRequestURI();
    int     _parseHTTPv();
    void    _parseHeaderFields();
    bool    _HTTPRequestComplete();

    unsigned int _strToBase(const std::string& str, std::ios_base& (*base)(std::ios_base&));
};

#endif
