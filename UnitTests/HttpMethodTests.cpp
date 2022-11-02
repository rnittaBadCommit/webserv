//
// Created by ymori on 2022/10/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"
#include "../srcs/httpMethod/MethodUtils.hpp"
#include "../srcs/HTTP/HTTPHead.hpp"

namespace DoGet{
 class DoGet : public ::testing::Test {
  protected:
   static void SetUpTestCase() {
     // First function only
     chdir("../.."); // Go to the project root directory
   }

   void SetUp() override {
     file_path = "UnitTests/testroot/var/www/index.html";
     dir_path = "UnitTests/testroot/var/www/do_not_delete";
     wrong_path = "UnitTests/testroot/var/www/fdsafdasf.html";
   }

   std::string file_path;
   std::string dir_path;
   std::string wrong_path;
 };

TEST_F(DoGet, SuccessCase1) {
  std::string path;
  ft::HTTPHead http_request;
  std::string response_message_str;

  EXPECT_EQ(do_get(http_request, file_path, response_message_str), 200);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;

}

TEST_F(DoGet, Case404_wrong_path) {
  std::string path;
  ft::HTTPHead http_request;
  std::string response_message_str;

  EXPECT_EQ(do_get(http_request, wrong_path, response_message_str), 404);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;

}

TEST_F(DoGet, Case404_dir_path) {
  std::string path;
  ft::HTTPHead http_request;
  std::string response_message_str;

  EXPECT_EQ(do_get(http_request, dir_path, response_message_str), 404);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;

}

}

namespace DoDelete{
 class DoDelete : public ::testing::Test {
  protected:
   static void SetUpTestCase() {
     // First function only
     chdir("../.."); // Go to the project root directory
   }

   void SetUp() override {
     delete_test_file_path = "UnitTests/testroot/var/www/delete_test_file.html";
     wrong_path = "UnitTests/testroot/var/www/fdsafdasf.html";
   }

   std::string delete_test_file_path;
   std::string wrong_path;
 };

TEST_F(DoDelete, ServerError500) {
  http_header_t http_header;
  std::string response_message_str;


  EXPECT_EQ(do_delete(http_header, wrong_path, response_message_str), 500);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;
}


TEST_F(DoDelete, SuccessCase) {
  http_header_t http_header;
  std::string response_message_str;

  std::ofstream delete_test_file;
  delete_test_file.open(delete_test_file_path);
  delete_test_file << "TEST" << std::endl;
  delete_test_file.close();

  EXPECT_EQ(do_delete(http_header, delete_test_file_path, response_message_str), 204);
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

