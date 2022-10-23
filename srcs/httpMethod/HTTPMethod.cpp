//
// Created by ymori on 2022/10/18.
//

#include "HTTPMethod.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <fstream>

#include "../httpResponse/HttpResponse.hpp"


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

/**
 *
 * @param http_header
 * @param file_path
 * @param response_message_str
 * @return
 */
int do_get(const http_header_t& http_header,
           std::string &file_path,
           std::string &response_message_str) {
  int response_status;
  std::stringstream response_message_stream;

  int ret_val;

  if (!file_path.empty()) {
    // TODO: index search
    int ret_val = 0;
    if (ret_val != 0) { // Resource not found
      response_message_stream << CreateErrorSentence(404);
      return (404);
    }
    // copy file path to path ?
  }
  // ret_val = stat
  if (ret_val < 0) {
    response_message_stream << CreateErrorSentence(404);
    return (404);
  }

  response_message_stream << "HTTP/1.1 200 OK" << CRLF;
  response_status = 200;

  response_message_stream << "Server: " << "42webserv" << "/1.0" << CRLF;
  response_message_stream << "Date: " << CreateDate() << CRLF;
  response_message_stream << "Last-Modified: " << CreateDate() << CRLF;

  // Force search results to text/html type
  if (!file_path.empty()) {
    // find type "x.html"
  } else {
    // find type file_path
  }

  // sending partial content

  // send full entry
  // Content-Type:
  // Content-Length:

  // don't send unless GET
//   if (http_header.at("Method") == "GET") {
//      // TODO: sendText in Socket class
//   }

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
