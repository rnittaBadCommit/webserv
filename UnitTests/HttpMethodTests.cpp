//
// Created by ymori on 2022/10/20.
//

#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"
#include "../srcs/httpMethod/MethodUtils.hpp"

namespace {

class MethodUtilsTests : public ::testing::Test {
 protected:
  void SetUp() {}
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

