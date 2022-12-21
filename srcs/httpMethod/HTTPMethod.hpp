//
// Created by ymori on 2022/10/18.
//

#ifndef WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_
#define WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_

#include <map>
#include <string>
#include "../HTTP/HTTPHead.hpp"
#include "../server/server.hpp"

typedef std::map<std::string, std::string> http_header_t;

int return1();

int do_put(std::string &response_message_str,
           const std::string &file_path,
           const std::string &http_body);

int do_get(std::string &response_message_str, const std::string &file_path);

int do_delete(std::string &response_message_str, const std::string &file_path);

int do_CGI(std::string &response_message_str,
           ft::ServerChild server_child,
           std::string file_path);

int disallow_method(std::string &response_message_str);

#endif //WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_
