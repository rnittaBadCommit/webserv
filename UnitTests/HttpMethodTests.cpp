//
// Created by ymori on 2022/10/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"
#include "../srcs/httpMethod/MethodUtils.hpp"
#include "../srcs/HTTP/HTTPHead.hpp"


namespace DoPut {
 class DoPut : public ::testing::Test {
  protected:
   static void SetUpTestCase() {
     // First function only
     chdir("../.."); // Go to the project root directory
   }

   void SetUp() override {
     file_path = "UnitTests/testroot/var/www/put_test.html";
     dir_path = "UnitTests/testroot/var/www/do_not_delete";
     new_add_path = "UnitTests/testroot/var/www/put-content.html";

     content_body = R"(<!DOCTYPE html><html lang="en"><head><meta charset="UTF-8"><title>PUT TEST</title></head><body><b1>YEAAAAAAAAAAAAAAAAAAAAAA</b1></body></html>)";
   }

   std::string file_path;
   std::string dir_path;
   std::string new_add_path;

   std::string content_body ;
 };

TEST_F(DoPut, NewAdd) {
  ft::HTTPHead http_head;
  std::string response_message_str;

  struct stat stat_buf = {};
  if (stat(new_add_path.c_str(), &stat_buf) == 0)
    remove(new_add_path.c_str());
  EXPECT_EQ(do_put(http_head, content_body, new_add_path, response_message_str), 201);

  std::cout << response_message_str << std::endl;

}

TEST_F(DoPut, AlreadyExist) {
  ft::HTTPHead http_head;
  std::string response_message_str;

  EXPECT_EQ(do_put(http_head, content_body, file_path, response_message_str), 204);

  std::cout << response_message_str << std::endl;

}
}


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

