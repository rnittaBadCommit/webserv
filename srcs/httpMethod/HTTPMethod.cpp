//
// Created by ymori on 2022/10/18.
//

#include "HTTPMethod.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

#include "../httpResponse/HttpResponse.hpp"
#include "../HTTP/HTTPHead.hpp"


/*
 * @arg
 *  Socket:
 *  Method:
 *  Headers:
 *  PATH:
 *  Search:
 *  (CGI)
 *
 * @return
 *  status code
 *
 *
 * The following implementations are omitted
 *
 * -- Check Mod, Match, Range and each processing
 * If-Modified-Since
 * If-Unmodified-Since
 * If-Match
 * If-None-Match
 * If-Range
 *
 * -- Check and judge status
 * 304
 * 412
 * 206
 * 200
 * 206
 * 200
 *
*/


/**
 *
 * @return GMT time in RFC7231 format
 */
std::string CreateDate() {
  char date[1024];
  time_t gmt_time;

  time(&gmt_time);
  strftime(date, 1024, "%a, %d %b %Y %X %Z", gmtime(&gmt_time)); // RFC7231

  return std::string(date);
}

/**
 *
 * @param status_code
 * @return
 */
std::string CreateErrorSentence(int status_code) {
  std::stringstream error_sentence;

// Error file create
//  << "<!DOCTYPE html>" << CRLF;
//  << "<html><head>" << CRLF;
//  << "<title>Error</title></head>" << CRLF;
//  << "<body>Error</body>" << CRLF;

  error_sentence << "HTTP/1.1 " << HttpResponse::GetResponseLine(status_code)
                 << CRLF; // TODO: check status code
  error_sentence << "Server: " << "42webserv" << "/1.0" << CRLF;
  error_sentence << "Date: " << CreateDate() << CRLF;
  error_sentence << "Content-Type: text/html";

  return error_sentence.str();
}

int do_put(ft::HTTPRequest &http_request,
           std::string &file_path,
           std::string &cgi,
           std::string &response_message_str) {

    std::string location;

    if (!file_path.empty()) {
        location = file_path;
    }

    size_t received_length = 0;
    size_t content_length = 424242; // tmp val
    std::stringstream received_content;

    for (size_t i = 0; i < content_length; i = i + received_length) {
        // write received content to receive_content.
        //
    }

    struct stat stat_buf = {};
    int ret_val = stat(location.c_str(), &stat_buf);

    if (ret_val == 0) {
        // file is already exist
        // overwrite
        // 204 No Content
    } else {
        // file is new added
        // 201 content created
    }
}

/**
 *
 * @param http_header
 * @param file_path
 * @param response_message_str
 * @return
 */
int do_get(ft::HTTPHead &http_request,
           std::string &file_path,
           std::string &response_message_str) {
  int response_status;
  std::stringstream response_message_stream;

  int ret_val;
  struct stat st = {};

  ret_val = stat(file_path.c_str(), &st);
  if (ret_val < 0 || !S_ISREG(st.st_mode)) {
    response_message_stream << CreateErrorSentence(404);
    response_message_str = response_message_stream.str();
    return (404);
  }

  response_message_stream << "HTTP/1.1 200 OK" << CRLF;
  response_status = 200;

  response_message_stream << "Server: " << "42webserv" << "/1.0" << CRLF;
  response_message_stream << "Date: " << CreateDate() << CRLF;
  response_message_stream << "Last-Modified: " << CreateDate() << CRLF;

//  // Force search results to text/html type
//  if (!file_path.empty()) {
//    // find type "x.html"
//  } else {
//    // find type file_path
//  }

  // sending partial content

  // send full entry
  // Content-Type:
  response_message_stream << "Content-Type: " << "text/html" << CRLF;
  // Content-Length:
  response_message_stream << "Content-Lenght: " << st.st_size << CRLF;

  // send body
  response_message_stream << CRLF;
  // file read
  std::ifstream reading_file;
  std::string reading_line_buf;
  reading_file.open(file_path.c_str());
  while (std::getline(reading_file, reading_line_buf))
    response_message_stream << reading_line_buf << CRLF;

  response_message_str = response_message_stream.str();
  return response_status;
}


/**
 *
 * @param http_header
 * @param file_path
 * @param response_message_str
 * @return
 */
int do_delete(const http_header_t& http_header,
              std::string &file_path,
              std::string &response_message_str) {
  int response_status;
  std::stringstream response_message_stream;
  std::string delete_dir = "ok";

  // Range not allowed for DELETE
//  if (http_header.find("Range :") == http_header.end()) {
//    response_message_stream << CreateErrorSentence(501);
//    response_message_str = response_message_stream.str();
//    return 501;
//  }

  // unlink
  int ret = unlink(file_path.c_str());
  // TODO: check errno ?
  if (ret == 0) {
    response_message_stream << "HTTP/1.1 204 No Content" << CRLF;
    response_status = 204;
  } else {
    response_message_stream << "HTTP/1.1 500 Server Error" << CRLF;
    response_status = 500;
  }

  response_message_stream << "Server: " << "42webserv" << "/1.0" << CRLF;
  response_message_stream << "Date: " << CreateDate() << CRLF;

  response_message_str = response_message_stream.str();
  return response_status;
}

int do_http() {
  std::stringstream send_data;

  return 0;
}
