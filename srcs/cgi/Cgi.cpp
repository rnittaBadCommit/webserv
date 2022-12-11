//
// Created by yuumo on 2022/11/07.
//

#include <cstdlib>
#include <unistd.h>
#include <cerrno>
#include <vector>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include "Cgi.hpp"

Cgi::Cgi() {
}

/**
 *
 * @param request_method
 *
 * TODO: We must build this function
 * - set environment
 */
void Cgi::CreateEnvMap(std::string &request_method) {
  cgi_env_val_["SERVER_SOFTWARE"] = "42";
  cgi_env_val_["GATEWAY_INTERFACE"] = "CGI/1.1";
  cgi_env_val_["SERVER_PROTOCOL"] = "HTTP/1.1";
  cgi_env_val_["SERVER_PORT"] = "80";
  cgi_env_val_["SERVER_NAME"] = "webserv";
  cgi_env_val_["REQUEST_METHOD"] = "GET";
  cgi_env_val_["QUERY_STRING"] = "query_string";
  cgi_env_val_["SCRIPT_NAME"] = "script_name"; // ?
  cgi_env_val_["CONTENT_LENGTH"] = "42";
  cgi_env_val_["CONTENT_TYPE"] = "html";
  cgi_env_val_["PATH_INFO"] = "";
  cgi_env_val_["REQUEST_URI"] = "";
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
    std::string m = "method_name";

    Cgi::CreateEnvMap(m);
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
    ret_val_child = chdir("/var/www/cgi-bin");
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
    argv[0] = strdup("/bin/python3");
    if (argv[0] == NULL) {
      free(argv);
      exit(1);
    }
    argv[1] = strdup("test_utils/cgi/cgi-hello-python.cgi");
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
    ret_val_child = execve("/bin/python3", argv, environ);

    free(argv[0]);
    free(argv[1]);
    free(argv);

    exit(ret_val_child);
  }

  close(child_socket);
}