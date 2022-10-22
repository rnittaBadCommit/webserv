//
// Created by ymori on 2022/10/20.
//

#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"
#include "../srcs/httpMethod/MethodUtils.hpp"

namespace {
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

}

namespace {

class MethodUtilsTests : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(MethodUtilsTests, Case1) {
  std::string uri = "/42tokyo?a=100";
  EXPECT_EQ(get_uri(uri), "/42tokyo");
}

TEST_F(MethodUtilsTests, Case2) {
  std::string uri = "/42tokyo";
  EXPECT_EQ(get_uri(uri), "/42tokyo");
}

TEST_F(MethodUtilsTests, Case3) {
  std::string uri = "/42tokyo?";
  EXPECT_EQ(get_uri(uri), "/42tokyo");
}

TEST_F(MethodUtilsTests, Case4) {
  std::string uri = "";
  EXPECT_EQ(get_uri(uri), "");
}
}

