//
// Created by yuumo on 2022/11/07.
//

#ifndef WEBSERV_SRCS_CGI_CGI_HPP_
#define WEBSERV_SRCS_CGI_CGI_HPP_

#include <string>
#include <map>
#include "server/server.hpp"

class Cgi {
 public:
  Cgi(ft::ServerChild server_child);
  ~Cgi();
  void Execute();

  /*
   * Getter
   */
  int GetCgiSocket() const;

 private:
  std::string cgi_path_;
  std::string query_string_;
  std::map<std::string, std::string> cgi_env_val_;
  int         cgi_socket_;

  // Server child
  std::string request_method_;
  std::string script_name_;

  void CreateEnvMap();
  void SetEnv();
  static int change_fd(int from, int to);
};

#endif //WEBSERV_SRCS_CGI_CGI_HPP_
