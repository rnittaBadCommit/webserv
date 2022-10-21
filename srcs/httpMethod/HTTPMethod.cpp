//
// Created by ymori on 2022/10/18.
//

#include "HTTPMethod.hpp"

#include <unistd.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include "../httpResponse/HttpResponse.hpp"

typedef std::map<std::string, std::string> http_header_t;

/**
 * Persistent
 * Chunked
 *
*/

/**
 *
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
*/
int executeGet() {
  // Temporary valuables
  std::string path = "/home";
  std::string location;
  std::string cgi;

  // Check PATH
  if (!path.empty()) {
    location = path;
  } else {
    // TODO: send Error message "Location not found" to client
    return 404;
  }

  // Skip Auth

  // TODO: Index search
  // <uri>?<param>&<param>&...

  std::string index = "ok";

  if (!index.empty()) {

  }

  /*
   * Check and judge status
   *
   * If-Modified-Since
   * If-Unmodified-Since
   * If-Match
   * If-None-Match
   * If-Range
   *
   * 304
   * 412
   * 206
   * 200
   * 206
   * 200
   */

  /*
   * Response Header
   */

  std::string method = "GET";
  std::string type = "text";

  // send entity
  if (method == "GET") {
    if (type == "binary") {
      /*
       * TODO: sentBinary in Socket class
       * sendBinary(path)
       */
    } else {
      /*
       * TODO: sendText in Socket class
       * sendText(path)
       */
    }
  }
}

std::string CreateErrorSentence(int status_code) {
  std::stringstream error_sentence;

  char date[1024];
  time_t gmt_time;
  time(&gmt_time);
  strftime(date, 1024, "%a, %d %b %Y %X %Z", gmtime(&gmt_time)); // RFC7231

// Error file create
//  << "<!DOCTYPE html>" << CRLF;
//  << "<html><head>" << CRLF;
//  << "<title>Error</title></head>" << CRLF;
//  << "<body>Error</body>" << CRLF;

  error_sentence << "HTTP/1.1 " << HttpResponse::GetResponseLine(status_code)
                 << CRLF; // TODO: check status code
  error_sentence << "Server: " << "42webserv" << "/1.0" << CRLF;
  error_sentence << "Content-Type: text/html" << CRLF;

  return error_sentence.str();
}

int do_delete(http_header_t http_header,
              std::string &file_path,
              std::string &response_message_str) {
  int response_status;
  std::stringstream response_message_stream;
  std::string delete_dir = "ok";

  // Range not allowed for DELETE
  if (http_header.find("Range :") == http_header.end()) {
    response_message_stream << CreateErrorSentence(501);
    return 501;
  }

  // unlink
  int ret = unlink(file_path.c_str());
  // TODO: check errno
  if (ret == 0) {
    response_message_stream << "HTTP/1.1 204 No Content" << CRLF;
    response_status = 204;
  } else {
    response_message_stream << "HTTP/1.1 500 Server Error" << CRLF;
    response_status = 500;
  }

  // Server:
  response_message_stream << "Server: " << "42webserv" << "/1.0" << CRLF;

  // Date:
  char date[1024];
  time_t gmt_time;
  time(&gmt_time);
  strftime(date, 1024, "%a, %d %b %Y %X %Z", gmtime(&gmt_time)); // RFC7231

  response_message_str = response_message_stream.str();
  return response_status;
}

int do_http() {
  std::stringstream send_data;

  return 0;
}
