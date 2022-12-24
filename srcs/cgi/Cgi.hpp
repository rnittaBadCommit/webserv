//
// Created by yuumo on 2022/11/07.
//

#ifndef WEBSERV_SRCS_CGI_CGI_HPP_
#define WEBSERV_SRCS_CGI_CGI_HPP_

#include <string>
#include <map>
#include "../server/serverChild.hpp"

class Cgi {
 public:
  Cgi(ft::ServerChild server_child, const std::string& query_string);
  ~Cgi();
  void Execute();

  /*
   * Getter
   */
  int GetCgiSocket() const;

 private:
  std::string cgi_path_;
  std::map<std::string, std::string> cgi_env_val_;
  int         cgi_socket_;

  /*
   * Environment
   */
  // PATH info
  std::string query_string_;

  // Server child
  std::string request_method_;
  std::string script_name_;

  // Location config
  std::string cgi_extension_;
  std::string bin_path_;

  // Server config
  std::string server_name_;
  unsigned int server_port_;

  void CreateEnvMap();
  void SetEnv();
  static int change_fd(int from, int to);
};

#endif //WEBSERV_SRCS_CGI_CGI_HPP_
