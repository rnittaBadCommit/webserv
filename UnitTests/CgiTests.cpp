//
// Created by yuumo on 2022/11/10.
//

#include <gtest/gtest.h>
#include "../srcs/cgi/Cgi.hpp"
#include "../srcs/server/server.hpp"

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
  Cgi c;
  c.Execute();

  // Print debug
  std::cout << "CGI socket: " << c.GetCgiSocket() << std::endl;
  char *buf[1024];
  read(c.GetCgiSocket(), buf, 1024);
  printf("%s\n", buf);
}
}
