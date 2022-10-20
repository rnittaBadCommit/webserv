//
// Created by ymori on 2022/10/20.
//

#include "gtest/gtest.h"
#include "../srcs/httpMethod/HTTPMethod.hpp"

 class HttpMethodTests : public ::testing::Test {
  protected:
   void SetUp() {}
 };

TEST_F(HttpMethodTests, Case1) {
  EXPECT_EQ(return1(), 1);
}

