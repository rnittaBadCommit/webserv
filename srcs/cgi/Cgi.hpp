//
// Created by yuumo on 2022/11/07.
//

#ifndef WEBSERV_SRCS_CGI_CGI_HPP_
#define WEBSERV_SRCS_CGI_CGI_HPP_

#include <string>
#include <map>

class Cgi {
 public:
  Cgi();
  void Execute();

 private:
  std::string cgi_path_;
  std::string query_string_;
  std::map<std::string, std::string> cgi_env_val_;

  void CreateEnvMap(std::string &request_method);
  void SetEnv();
  static int change_fd(int from, int to);
};

#endif //WEBSERV_SRCS_CGI_CGI_HPP_
