#pragma once
#ifndef HTTPHEAD_HPP
# define HTTPHEAD_HPP

#include <string>
#include <limits>
#include <cstddef>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <exception>
#include <stack>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "../utils/utils.hpp"

namespace ft {
    enum            HTTPParseStatus { requestLine, headerFields, readChunks, readStraight, complete };

    const static std::string    DELIM = "\r\n";
    const static std::string    BREAK = "\r\n\r\n";
    const static std::string    SP = " ";
    const static std::string    CN = ":";
    const static std::string    HTTPV = "HTTP/1.1";
    const static size_t         MAXBUFFER = 8000;
    const static size_t         MAXHEADERS = 100;

    class HTTPHead {
    public:
        typedef std::map<std::string, std::string>  header_type;
        typedef std::pair<std::string, std::string> header_value;

    private:

        int             _responseCode;
        HTTPParseStatus _parseStatus;
        std::string     _requestMethod;
        std::string     _requestURI;
        std::string     _HTTPv;
        header_type     _headerFields;
        header_value    _currentHeader; 
        std::string     _save;


    public:
        HTTPHead();
        HTTPHead(const HTTPHead& src);
        HTTPHead& operator=(const HTTPHead& rhs);
        ~HTTPHead();

        int     Parse(const std::string& request);
        void    ParseRequestURI();
    
        const std::string&      GetHost() const;
        const int&              GetResponseCode() const;
        const HTTPParseStatus&  GetParseStatus() const;
        const std::string&      GetRequestMethod() const;
        std::string&            GetRequestURI();
        const std::string&      GetHTTPv() const;
        header_type&            GetHeaderFields();
        const std::string&      getSave() const;


    private:

        void    parseRequestLine();
        void    parseHeaderFields();
        void    toLower(std::string& str);
        bool    multiInclusion();  
        void    _throw(int responseCode, const std::string& message);
    public:
        void    PrintRequest();
    };
}

#endif
