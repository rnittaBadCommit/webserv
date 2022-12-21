//
// Created by yuumo on 2022/10/23.
//

#include "gtest/gtest.h"
#include "../srcs/HTTP/HTTPHead.hpp"

namespace {
 class HTTPRequestTest : public ::testing::Test {

 };

TEST_F(HTTPRequestTest, Case1) {
  ft::HTTPHead req;
  std::string     line = "GET http://example.com/private/index.html HTTP/1.1\r\nhost: hostname\r\n\r\n";

  int ret = req.Parse(std::string(line));
  EXPECT_EQ(req.GetRequestMethod(), "GET");
  EXPECT_EQ(req.GetRequestURI(), "http://example.com/private/index.html");
  std::cout << "Host:           " << req.GetHost() << std::endl;
  std::cout << "ResponseCode:   " << req.GetResponseCode() << std::endl;
  std::cout << "ParseStatus:    " << req.GetParseStatus() << std::endl;
  std::cout << "RequestMethod:  " << req.GetRequestMethod() << std::endl;
  std::cout << "RequestURI:     " << req.GetRequestURI() << std::endl;
  std::cout << "HTTPv:          " << req.GetHTTPv() << std::endl;
//  std::cout << "HeaderFields:   " << req.GetHeaderFields() << std::endl;
  std::cout << "Save:           " << req.getSave() << std::endl;
}

TEST_F(HTTPRequestTest, CGICase) {
  ft::HTTPHead req;
  std::string  line = "GET http://example.com/cgi-bin/script.cgi?a=100&b=200 HTTP/1.1\r\nhost: hostname\r\n\r\n";

  int ret = req.Parse(std::string(line));
  std::cout << "Host:           " << req.GetHost() << std::endl;
  std::cout << "ResponseCode:   " << req.GetResponseCode() << std::endl;
  std::cout << "ParseStatus:    " << req.GetParseStatus() << std::endl;
  std::cout << "RequestMethod:  " << req.GetRequestMethod() << std::endl;
  std::cout << "RequestURI:     " << req.GetRequestURI() << std::endl;
  std::cout << "HTTPv:          " << req.GetHTTPv() << std::endl;
//  std::cout << "HeaderFields:   " << req.GetHeaderFields() << std::endl;
  std::cout << "Save:           " << req.getSave() << std::endl;
}
}
