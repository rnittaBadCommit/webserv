//
// Created by yuumo on 2022/10/27.
//

#include "gtest/gtest.h"

#include "../srcs/utils/utils.hpp"
#include "../srcs/httpMethod/AutoIndex.hpp"

namespace RenderHtml {
 class RenderHtml : public ::testing::Test {
  protected:
   static void SetUpTestCase() {
     chdir("../..");
   }
 };

TEST_F(RenderHtml, SuccessCase1) {
  std::ofstream successHtmlFile;
  std::set<std::string> ret;

  successHtmlFile.open("successHtmlFile01.html");

  ret = ft::CreateDirectoryList("UnitTests/testroot/");
  successHtmlFile << render_html("UnitTests/testroot/", ret);
  successHtmlFile.close();
}
}