//
// Created by yuumo on 2022/10/27.
//

#include <fstream>

#include "gtest/gtest.h"
#include "../srcs/utils/utils.hpp"

namespace CreateDirectoryListTests {
class CreateDirectoryListTests : public ::testing::Test{
 protected:
  static void SetUpTestCase() {
    chdir("../..");
  }
};

TEST_F(CreateDirectoryListTests, SuccessCase1) {
  std::set<std::string> ret;

  ret = ft::CreateDirectoryList("UnitTests/testroot/");
  for (const auto & iter : ret)  {
    std::cout << iter << std::endl;
  }
}

TEST_F(CreateDirectoryListTests, SuccessCase2) {
  std::set<std::string> ret;

  ret = ft::CreateDirectoryList("UnitTests/testroot/var/");
//  ret = ft::CreateDirectoryList("UnitTests/testroot/var"); // fail
  for (const auto & iter : ret)  {
    std::cout << iter << std::endl;
  }
}

}

