//
// Created by yuumo on 2022/10/23.
//

#include "gtest/gtest.h"
#include "../srcs/HTTP/HTTPHead.hpp"

namespace {
    class HTTPRequestTest : public ::testing::Test {

    };

    TEST_F(HTTPRequestTest, CaseGetURL) {
        ft::HTTPHead req;
        std::string line = "GET http://example.com/private/index.html HTTP/1.1\r\nhost: hostname\r\n\r\n";

        EXPECT_EQ(req.Parse(line), 0);

        EXPECT_EQ(req.GetRequestMethod(), "GET");
        EXPECT_EQ(req.GetRequestURI(), "http://example.com/private/index.html");
        EXPECT_EQ(req.GetHTTPv(), "HTTP/1.1");
        EXPECT_EQ(req.GetHost(), "hostname");
        EXPECT_EQ(req.GetResponseCode(), 200);
        EXPECT_EQ(req.GetParseStatus(), ft::complete);
        EXPECT_EQ(req.GetHeaderFields().find("host")->second, "hostname");

        req.ParseRequestURI();
        EXPECT_EQ(req.GetRequestURI(), "/private/index.html");
        EXPECT_EQ(req.GetHost(), "example.com");
        EXPECT_EQ(req.GetHeaderFields().find("host")->second, "example.com");
    }
}
