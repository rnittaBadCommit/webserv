//
// Created by yuumo on 2022/10/27.
//

#ifndef WEBSERV_SRCS_HTTPMETHOD_AUTOINDEX_HPP_
#define WEBSERV_SRCS_HTTPMETHOD_AUTOINDEX_HPP_

std::string render_html(const std::string& dirpath_root, const std::set<std::string>& dirpath_list);

#endif //WEBSERV_SRCS_HTTPMETHOD_AUTOINDEX_HPP_
