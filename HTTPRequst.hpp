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
    enum            ParseStatus { requestLine, headerFields, readChunks, readStraight, complete };

    int             _errorStatus;
    ParseStatus     _parseStatus;
    std::string     _requestMethod;
    std::string     _requestURI;
    std::string     _HTTPv;
    header_type     _headerFields;
    header_value    _currentHeader;
    unsigned int    _contentLength;
    std::string     _body;
    std::string     _save;
    std::string     _reqLineHeader;



public:
    HTTPRequest();
    ~HTTPRequest();

    int     Parse(const std::string& request);
    void    PrintRequest();
    const std::string& GetReqLineHeader();

 
    const std::string&  GetRequestMethod();
    const std::string&  GetRequestURI();
    const std::string&  GetHTTPv();
    const header_type&  GetHeaderFields();
    const std::string&  GetBody();

private:

    void        _parseRequestLine();
    bool        _parseHeaderFields();
    bool        _HTTPRequestComplete();
    void        _decideReadType();

    unsigned int _strToBase(const std::string& str, std::ios_base& (*base)(std::ios_base&));
};

#endif
