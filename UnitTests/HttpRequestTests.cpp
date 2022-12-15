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

        int ret = req.Parse(line);
        EXPECT_EQ(ret, 0);
        EXPECT_EQ(req.GetRequestMethod(), "GET");
        EXPECT_EQ(req.GetRequestURI(), "http://example.com/private/index.html");
        EXPECT_EQ(req.GetHost(), "hostname");
        req.ParseRequestURI();
        EXPECT_EQ(req.GetHost(), "example.com");
        std::cout << "host: " << req.GetHost() << std::endl;
        EXPECT_EQ(req.GetRequestURI(), "/private/index.html");
        EXPECT_EQ(req.GetResponseCode(), 200);
        std::cout << "RC: " << req.GetResponseCode() << std::endl;
        EXPECT_EQ(req.GetParseStatus(), ft::complete);
        EXPECT_EQ(req.GetHTTPv(), "HTTP/1.1");
        EXPECT_EQ(req.GetHeaderFields().find("host")->second, "hostname");
    }

    TEST_F(HTTPRequestTest, CaseGetURI) {
        ft::HTTPHead req;
        std::string line = "GET /private/index.html HTTP/1.1\r\nhost: hostname\r\n\r\n";

        int ret = req.Parse(std::string(line));
        EXPECT_EQ(ret, 0);
        EXPECT_EQ(req.GetRequestMethod(), "GET");
        EXPECT_EQ(req.GetRequestURI(), "/private/index.html");
        EXPECT_EQ(req.GetHost(), "hostname");
        req.ParseRequestURI();
        EXPECT_EQ(req.GetHost(), "hostname");
        EXPECT_EQ(req.GetRequestURI(), "/private/index.html");
        EXPECT_EQ(req.GetResponseCode(), 200);
        EXPECT_EQ(req.GetParseStatus(), ft::complete);
        EXPECT_EQ(req.GetHTTPv(), "HTTP/1.1");
        EXPECT_EQ(req.GetHeaderFields().find("host")->second, "hostname");
    }

    TEST_F(HTTPRequestTest, CaseCGI) {
        ft::HTTPHead req;
        std::string line = "GET /cgi-bin/script.cgi/?10+20 HTTP/1.1\r\nhost:hostname\r\n\r\n";

        int ret = req.Parse(std::string(line));
        EXPECT_EQ(ret, 0);
        EXPECT_EQ(req.GetRequestMethod(), "GET");
        EXPECT_EQ(req.GetRequestURI(), "/cgi-bin/script.cgi/?10+20");
        EXPECT_EQ(req.GetHost(), "hostname");
        req.ParseRequestURI();
        EXPECT_EQ(req.GetHost(), "hostname");
        EXPECT_EQ(req.GetRequestURI(), "/cgi-bin/script.cgi/?10+20");
        EXPECT_EQ(req.GetResponseCode(), 200);
        EXPECT_EQ(req.GetParseStatus(), ft::complete);
        EXPECT_EQ(req.GetHTTPv(), "HTTP/1.1");
        EXPECT_EQ(req.GetHeaderFields().find("host")->second, "hostname");
    }

    TEST_F(HTTPRequestTest, CasePOST) {
        ft::HTTPHead req;
        std::string line = "POST / HTTP/1.1\r\nhost:hostname\r\ncontent-length:5\r\n\r\n";
        std::string body = "hey\r\n";

        int ret = req.Parse(std::string(line + body));
        EXPECT_EQ(ret, 0);
        EXPECT_EQ(req.GetRequestMethod(), "POST");
        EXPECT_EQ(req.GetRequestURI(), "/");
        EXPECT_EQ(req.GetHost(), "hostname");
        EXPECT_EQ(req.GetResponseCode(), 200);
        EXPECT_EQ(req.GetParseStatus(), ft::complete);
        EXPECT_EQ(req.GetHTTPv(), "HTTP/1.1");
        EXPECT_EQ(req.GetHeaderFields().find("host")->second, "hostname");
        EXPECT_EQ(req.GetHeaderFields().find("content-length")->second, "5");
        EXPECT_EQ(req.getSave(), body);
    }
}