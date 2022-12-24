//
// Created by yuumo on 2022/11/07.
//

/*
 * According to RFC 3875, CGI responses can be document-response, local-redir-response, client-redir-response, client-redirdoc-response, but our implementation is limited to document-response.
 */


#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <vector>
#include <cstring>
#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <sys/socket.h>
#include <cstdio>
#include <sys/wait.h>
#include "Cgi.hpp"

Cgi::Cgi(ft::ServerChild server_child,
         const std::string &file_path,
         const std::string &script_name,
         const std::string &query_string)
    : cgi_path_(file_path),
      query_string_(query_string),
      request_method_(server_child.Get_HTTPHead().GetRequestMethod()),
      script_name_(script_name),
      cgi_extension_(server_child.Get_location_config().getCgiExtension().first),
      bin_path_(server_child.Get_location_config().getCgiExtension().second),
      server_name_(server_child.Get_server_config().getServerName()),
      server_port_(server_child.Get_server_config().getListen())
      {
}

Cgi::~Cgi() {
  close(cgi_socket_);
}

/**
 *
 * @param request_method
 *
 * TODO: We must build this function
 * - set environment
 *
 * https://datatracker.ietf.org/doc/html/rfc3875#section-4-1
 * http://bashhp.web.fc2.com/WWW/header.html
 */
void Cgi::CreateEnvMap() {
  cgi_env_val_["SERVER_SOFTWARE"] = "42";
  cgi_env_val_["GATEWAY_INTERFACE"] = "CGI/1.1";
  cgi_env_val_["SERVER_PROTOCOL"] = "HTTP/1.1"; // tmp

  std::stringstream server_port_string_; // server_port_ is unsigned int.
  server_port_string_ << server_port_;
  cgi_env_val_["SERVER_PORT"] = server_port_string_.str();

  cgi_env_val_["SERVER_NAME"] = server_name_;
  cgi_env_val_["REQUEST_METHOD"] = request_method_;
  cgi_env_val_["SCRIPT_NAME"] = script_name_;

  // POST によってフォームを受信する場合に、標準入力から読み込む必要のあるbyte数
  cgi_env_val_["CONTENT_LENGTH"] = "42"; // TODO: get_content_length()

  // POST によってフォームを受信する場合
  cgi_env_val_["CONTENT_TYPE"] = "html"; // tmp

  // for GET
  cgi_env_val_["QUERY_STRING"] = query_string_;
  cgi_env_val_["PATH_INFO"] = "";

  cgi_env_val_["REQUEST_URI"] = ""; // Not supported
}

/**
 * @brief set environ based on cgi_env_val_
 */
void  Cgi::SetEnv() {
  for (std::map<std::string, std::string>::const_iterator iter = cgi_env_val_.begin(); iter != cgi_env_val_.end(); ++iter) {
    setenv(iter->first.c_str(), iter->second.c_str(), 1); // overwrite
  }
}

/**
 * @param from
 * @param to
 * @return
 */
int Cgi::change_fd(int from, int to) {
  int ret_val;

  if (from == to) {
    return 0;
  }
  close(to);
  ret_val = dup2(from, to);
  return ret_val;
}

/**
 * @brief Execute CGI.
 *
 * error:
 * とりあえずリターンしておく
 * とりあえずexitしておく
 *
 * CGI用の双方向通信を作成する
 */
void Cgi::Execute() {
  int ret_val;
  int socket_fds[2];

  ret_val = socketpair(AF_UNIX, SOCK_STREAM, 0, socket_fds);
  if (ret_val == -1) {
    std::cerr << "socket error" << std::endl;
    return;
  }

  int parent_socket = socket_fds[0];
  int child_socket = socket_fds[1];

  pid_t pid = fork();
  if (pid < 0) { // fork error
    // TODO: error 500
    std::cerr << "fork failed" << std::endl;
    close(parent_socket);
    close(child_socket);
    return;
  }
  if (pid == 0) { // child
    int ret_val_child = 1;

    Cgi::CreateEnvMap();
    Cgi::SetEnv();

    close(parent_socket);

    /*
     * Connect STDIN and STDOUT to the file descriptor of a socket.
     */
    ret_val_child = change_fd(child_socket, STDIN_FILENO);
    if (ret_val_child < 0) {
      exit(ret_val_child);
    }
    ret_val_child = change_fd(child_socket, STDOUT_FILENO);
    if (ret_val_child < 0) {
      exit(ret_val_child);
    }


    /*
     * Change directory
     */
    ret_val_child = chdir("./");
    if (ret_val_child != 0) {
      exit(ret_val_child);
    }

    /*
     * Create argv
     */
    char **argv = (char **)malloc(sizeof(char *) * 3);
    if (argv == NULL) {
      exit(1);
    }
    argv[0] = strdup(bin_path_.c_str());
    if (argv[0] == NULL) {
      free(argv);
      exit(1);
    }
    argv[1] = strdup(cgi_path_.c_str());
    if (argv[1] == NULL) {
      free(argv[0]);
      free(argv);
      exit(1);
    }
    argv[2] = NULL;

    /*
     * Execution CGI
     */
    errno = 0;
    ret_val_child = execve(bin_path_.c_str(), argv, environ);
    perror("execve failed");

    free(argv[0]);
    free(argv[1]);
    free(argv);

    exit(ret_val_child);
  }

  // Set cgi socket
  cgi_socket_ = parent_socket;

  int status;
  waitpid(pid, &status, 0);

  // TODO: delete (This is debug)
  if (WEXITSTATUS(status) != 0) {
    std::cerr << "The child process exited with an error" << std::endl;
  } else {
    std::cerr << "The child process exited successfully" << std::endl;
  }

  close(child_socket);
}

//TODO: void  Cgi::MakeDocumentResponse

/*
 * Getter
 */
int Cgi::GetCgiSocket() const {
  return cgi_socket_;
}
