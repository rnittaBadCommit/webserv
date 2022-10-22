//
// Created by yuumo on 2022/10/23.
//

#include "gtest/gtest.h"
#include "../srcs/HTTP/HTTPRequst.hpp"

namespace {
 class HTTPRequestTest : public ::testing::Test {

 };

TEST_F(HTTPRequestTest, Case1) {
  ft::HTTPRequest req("1000000");
  std::string     line = "GET /private/index.html HTTP/1.1";

  int rlt = req.Parse(std::string(line));
  EXPECT_EQ(req.GetRequestMethod(), "GET");
  EXPECT_EQ(req.GetRequestURI(), "/private/index.html");
}
}
