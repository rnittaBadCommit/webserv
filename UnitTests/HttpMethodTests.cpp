//
// Created by ymori on 2022/10/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"
#include "../srcs/httpMethod/MethodUtils.hpp"

namespace DoGet{
 class DoGet : public ::testing::Test {
  protected:
   void SetUp() override {

   }
 };

TEST_F(DoGet, PathEmpty) {
  std::string path;
  http_header_t http_header;
  std::string response_message_str;

  do_get(http_header, path, response_message_str);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;
}

}

namespace DoDelete{
 class DoDelete : public ::testing::Test {
  protected:
   void SetUp() override {
     ok_path = "/tmp/www/index.html";
   }

   std::string ok_path;
 };

TEST_F(DoDelete, ServerError500) {
  http_header_t http_header;
  std::string response_message_str;

  EXPECT_EQ(do_delete(http_header, ok_path, response_message_str), 501);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;
}

TEST_F(DoDelete, ServerError501) {
  http_header_t http_header {
      {"Range :", "100"}
  };
  std::string response_message_str;

  EXPECT_EQ(do_delete(http_header, ok_path, response_message_str), 500);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;
}

TEST_F(DoDelete, SuccessCase) {
  http_header_t http_header {
      {"Range :", "100"}
  };
  std::string response_message_str;

//  char tmp[256];
//  getcwd(tmp, 256);
//  std::cout << "pwd: " << tmp << std::endl;
//
  chdir("../..");
//  getcwd(tmp, 256);
//  std::cout << "pwd: " << tmp << std::endl;

  std::string test_file_path = "UnitTests/testroot/var/www/delete_test_file.html";

  std::ofstream delete_test_file;
  delete_test_file.open(test_file_path);
  delete_test_file << "TEST" << std::endl;
  delete_test_file.close();

  EXPECT_EQ(do_delete(http_header, test_file_path, response_message_str), 204);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;
}
}


namespace MethodUtils{

class MethodUtils : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(MethodUtils, Case1) {
  std::string uri = "/42tokyo?a=100";
  EXPECT_EQ(get_uri(uri), "/42tokyo");
}

TEST_F(MethodUtils, Case2) {
  std::string uri = "/42tokyo";
  EXPECT_EQ(get_uri(uri), "/42tokyo");
}

TEST_F(MethodUtils, Case3) {
  std::string uri = "/42tokyo?";
  EXPECT_EQ(get_uri(uri), "/42tokyo");
}

TEST_F(MethodUtils, Case4) {
  std::string uri = "";
  EXPECT_EQ(get_uri(uri), "");
}
}

