//
// Created by yuumo on 2022/10/14.
//

#ifndef WEBSERV_SRCS_HTTPRESPONSE_HPP_
#define WEBSERV_SRCS_HTTPRESPONSE_HPP_

class HttpResponse {
 public:
  std::string GetResponseMessage(int status_code);

 private:
  std::string CreateResponseNoSuccessBody_(int status_code);
  std::string GetResponseLine_(int status_code);
};

#endif //WEBSERV_SRCS_HTTPRESPONSE_HPP_
