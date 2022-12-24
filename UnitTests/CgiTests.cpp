//
// Created by yuumo on 2022/11/10.
//

#include <gtest/gtest.h>
#include "../srcs/cgi/Cgi.hpp"

namespace CgiTest{
 class CgiTest : public ::testing::Test {
  protected:
   static void SetUpTestCase() {
     // First function only
     chdir("../.."); // Go to the project root directory
   }
 };

TEST_F(CgiTest, SuccessCase1) {
//  ft::Server s;
//  ft::Server::
  ft::ServerChild server_child;
  std::string query_string_;
  Cgi c(server_child, query_string_);
  c.Execute();

  // Print debug
  std::cout << "CGI socket: " << c.GetCgiSocket() << std::endl;
  const int buf_size = 1024;
  char buf[buf_size];
  ssize_t n;
  n = read(c.GetCgiSocket(), buf, buf_size);
  buf[n] = '\0';
  std::cout << buf << std::endl;
}
}
