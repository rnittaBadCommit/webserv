//
// Created by 森　優大 on 2022/10/20.
//

#ifndef WEBSERV_SRCS_HTTPMETHOD_METHODUTILS_HPP_
#define WEBSERV_SRCS_HTTPMETHOD_METHODUTILS_HPP_

#include <string>

std::string get_uri_and_check_CGI(const std::string &szUri, bool &is_cgi);

#endif //WEBSERV_SRCS_HTTPMETHOD_METHODUTILS_HPP_
