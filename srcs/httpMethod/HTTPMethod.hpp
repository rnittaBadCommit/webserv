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

int do_put(const std::string &http_body,
           const std::string &file_path,
           std::string &response_message_str);

int do_get(const std::string &file_path,
           std::string &response_message_str);

int do_delete(const std::string &file_path,
              std::string &response_message_str);

int do_CGI(ft::ServerChild server_child,
           std::string &response_message_str,
           std::string file_path);

int disallow_method(std::string &response_message_str);

#endif //WEBSERV_SRCS_HTTPMETHOD_HTTPMETHOD_H_
