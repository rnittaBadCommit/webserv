//
// Created by yuumo on 2022/10/14.
//

#ifndef WEBSERV_SRCS_HTTPRESPONSE_HPP_
#define WEBSERV_SRCS_HTTPRESPONSE_HPP_

#define CRLF "\r\n"

class HttpResponse {
 public:
  HttpResponse();
  ~HttpResponse();
  static std::string GetResponseLine(int status_code);
  static std::string GetResponseMessage(int status_code);
  static std::string CreateResponseNoSuccessBody(int status_code);

 private:
};

#endif //WEBSERV_SRCS_HTTPRESPONSE_HPP_
