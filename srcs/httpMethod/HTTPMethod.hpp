//
// Created by ymori on 2022/10/18.
//

#ifndef WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_
#define WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_

#include <map>
#include <string>
#include "../HTTP/HTTPRequst.hpp"

typedef std::map<std::string, std::string> http_header_t;

int return1();

int do_get(ft::HTTPRequest& http_request,
           std::string &file_path,
           std::string &response_message_str);
int do_delete(const http_header_t& http_header,
              std::string &file_path,
              std::string &response_message_str);

#endif //WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_
