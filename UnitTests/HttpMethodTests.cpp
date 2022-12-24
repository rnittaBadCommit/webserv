//
// Created by ymori on 2022/10/20.
//

#include <fstream>
#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"
#include "../srcs/httpMethod/MethodUtils.hpp"
#include "../srcs/HTTP/HTTPHead.hpp"
#include "../srcs/cgi/Cgi.hpp"


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
  EXPECT_EQ(do_put(response_message_str, new_add_path, content_body), 201);

  std::cout << response_message_str << std::endl;

}

TEST_F(DoPut, AlreadyExist) {
  ft::HTTPHead http_head;
  std::string response_message_str;

  EXPECT_EQ(do_put(response_message_str, file_path, content_body), 204);

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

  EXPECT_EQ(do_get(response_message_str, file_path), 200);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;

}

TEST_F(DoGet, Case404_wrong_path) {
  std::string path;
  ft::HTTPHead http_request;
  std::string response_message_str;

  EXPECT_EQ(do_get(response_message_str, wrong_path), 404);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;

}

TEST_F(DoGet, Case404_dir_path) {
  std::string path;
  ft::HTTPHead http_request;
  std::string response_message_str;

  EXPECT_EQ(do_get(response_message_str, dir_path), 404);
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


  EXPECT_EQ(do_delete(response_message_str, wrong_path), 500);
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

  EXPECT_EQ(do_delete(response_message_str, delete_test_file_path), 204);
  std::cout << "Server Error*****" << std::endl;
  std::cout << response_message_str << std::endl;
  std::cout << "*****" << std::endl;
}
}


namespace DoCGI{
 class DoCGI : public ::testing::Test {
  protected:
   static void SetUpTestCase() {
     // First function only
     chdir("../.."); // Go to the project root directory
   }

   void SetUp() override {}
 };

TEST_F(DoCGI, Case1) {
  ft::ServerChild server_child;

  std::string response_message_str;

  do_CGI(response_message_str, server_child, std::string());

  std::cout << response_message_str << std::endl;
}
}


namespace MethodUtils{

class MethodUtils : public ::testing::Test {
 protected:
  void SetUp() override {}
};

TEST_F(MethodUtils, Case1) {
  std::string uri = "/42tokyo?a=100";
  bool is_cgi = false;
  std::string query_string_;
  EXPECT_EQ(get_uri_and_check_CGI(uri, query_string_, is_cgi), "/42tokyo");
  EXPECT_EQ(is_cgi, true);
  EXPECT_EQ(query_string_, "a=100");
}

TEST_F(MethodUtils, Case2) {
  std::string uri = "/42tokyo";
  bool is_cgi = false;
  std::string query_string_;
  EXPECT_EQ(get_uri_and_check_CGI(uri, query_string_, is_cgi), "/42tokyo");
  EXPECT_EQ(is_cgi, false);
  EXPECT_EQ(query_string_, "");
}

TEST_F(MethodUtils, Case3) {
  std::string uri = "/42tokyo?";
  bool is_cgi = false;
  std::string query_string_;
  EXPECT_EQ(get_uri_and_check_CGI(uri, query_string_, is_cgi), "/42tokyo");
  EXPECT_EQ(is_cgi, false);
  EXPECT_EQ(query_string_, "");
}

TEST_F(MethodUtils, Case4) {
  std::string uri = "";
  bool is_cgi = false;
  std::string query_string_;
  EXPECT_EQ(get_uri_and_check_CGI(uri, query_string_, is_cgi), "");
  EXPECT_EQ(is_cgi, false);
  EXPECT_EQ(query_string_, "");
}

TEST_F(MethodUtils, Case5) {
  std::string uri = "/42tokyo?=";
  bool is_cgi = false;
  std::string query_string_;
  EXPECT_EQ(get_uri_and_check_CGI(uri, query_string_, is_cgi), "/42tokyo");
  EXPECT_EQ(is_cgi, true);
  EXPECT_EQ(query_string_, "=");
}

TEST_F(MethodUtils, Case6) {
  std::string uri = "/42tokyo?a=100&b=200&c=300";
  bool is_cgi = false;
  std::string query_string_;
  EXPECT_EQ(get_uri_and_check_CGI(uri, query_string_, is_cgi), "/42tokyo");
  EXPECT_EQ(is_cgi, true);
  EXPECT_EQ(query_string_, "a=100&b=200&c=300");
}
}

