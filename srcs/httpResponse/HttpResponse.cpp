//
// Created by yuumo on 2022/10/14.
//

#include <string>
#include <iostream>
#include <sstream>
#include "HttpResponse.hpp"
#include "status_code.hpp"


HttpResponse::HttpResponse() {};
HttpResponse::~HttpResponse() {};


/*
 * nginx
 *  - Server
 *    - nginx
 *  - Date
 *    - Mon, 28 Sep 1970 06:00:00 GMT
 *  - Content-Type
 *    - charset=
 *  - Connection
 *    - upgrade
 *    - keep-alive
 *    - close
 *  - Content-Length
 *  - Content-Encoding
 *  - Location
 *    - https://  80:65535
 *    - http
 *  - Last-Modified
 *  - Accept-Ranges
 *  - Expires
 *  - Cache-Control
 *  - ETag
 *  - Transfer-Encoding
 *    - chunked
 *  - Keep-Alive
 *    - timeout=
 *  // GZIP
 *  - Vary
 *    - Accept-Encoding
 */

std::string HttpResponse::GetResponseLine(int status_code) {
  switch (status_code) {
    case HTTP_OK:return "200 OK";
    case HTTP_CREATED:return "201 Created";
    case HTTP_ACCEPTED:return "202 Accepted";
    case HTTP_NO_CONTENT:return "204 No Content";
    case HTTP_PARTIAL_CONTENT:return "206 Partial Content";
    case HTTP_MOVED_PERMANENTLY:
      return "301 Moved Permanently";
    case HTTP_MOVED_TEMPORARILY:
      return "302 Moved Temporarily";
    case HTTP_SEE_OTHER:
      return "303 See Other";
    case HTTP_TEMPORARY_REDIRECT:
      return "307 Temporary Redirect";
    case HTTP_PERMANENT_REDIRECT:
      return "308 Permanent Redirect";
    case HTTP_BAD_REQUEST:
      return "400 Bad Request";
    case HTTP_UNAUTHORIZED:
      return "401 Unauthorized";
//    case HTTP_PAYMENT_REQUIRED:
    case HTTP_FORBIDDEN:
      return "403 Forbidden";
    case HTTP_NOT_FOUND:
      return "404 Not Found";
    case HTTP_NOT_ALLOWED:
      return "405 Not Allowed";
    case HTTP_REQUEST_TIME_OUT:
      return "408 Request Time-out";
    case HTTP_CONFLICT:
      return "409 Conflict";
//    case HTTP_GONE:
    case HTTP_LENGTH_REQUIRED:
      return "411 Length Required";
    case HTTP_PRECONDITION_FAILED:
      return "412 Precondition Failed";
    case HTTP_REQUEST_ENTITY_TOO_LARGE:
      return "413 Request Entity Too Large";
    case HTTP_REQUEST_URI_TOO_LARGE:
      return "414 Request-URI Too Large";
    case HTTP_UNSUPPORTED_MEDIA_TYPE:
      return "415 Unsupported Media Type";
    case HTTP_RANGE_NOT_SATISFIABLE:
      return "416 Requested Range Not Satisfiable";
    case HTTP_INTERNAL_SERVER_ERROR:
      return "500 Internal Server Error";
    case HTTP_NOT_IMPLEMENTED:
     return "501 Not Implemented";
    case HTTP_BAD_GATEWAY:
     return "502 Bad Gateway";
    case HTTP_SERVICE_UNAVAILABLE:
     return "503 Service Temporarily Unavailable";
    case HTTP_GATEWAY_TIME_OUT:
     return "504 Gateway Time-out";
    case HTTP_VERSION_NOT_SUPPORTED:
     return "505 HTTP Version Not Supported";
//    case HTTP_INSUFFICIENT_STORAGE:
//     return "507 Insufficient Storage";
    default:
      // TODO: ERROR
      return "ERROR NO OUTPUT";
  }
}

std::string HttpResponse::CreateResponseNoSuccessBody(int status_code) {
  std::stringstream response_body;

  response_body << "<html>" CRLF
                << "<head><title>"
                << GetResponseLine(status_code)
                << "</title></head>" CRLF
                << "<body>" CRLF
                << "<center><h1>"
                << GetResponseLine(status_code)
                << "</h1></center>" CRLF;

  return response_body.str();
}

std::string HttpResponse::GetResponseMessage(int status_code) {
  std::stringstream response_message;
  std::string error_response_body = status_code >= 300 ? CreateResponseNoSuccessBody(status_code) : "";

  // Temporary val
  char date[1024];
  time_t gmt_time;
  time(&gmt_time);
  strftime(date, 1024, "%a, %d %b %Y %X %Z", gmtime(&gmt_time)); // RFC7231
  std::string content_type = "text/html";
  std::string content_charset = "en";
  std::string accept_ranges = "bytes";
  size_t content_length = 424242;
  std::string host_data = "example.com";
  std::string location = "/index.html";
#define HTTP_SSL 1
  unsigned int http_port = 80;
  bool chunked = true;
  bool keep_alive = true;
  std::string keep_alive_header = "5";

  // Response line
  response_message << "HTTP/1.1 " << GetResponseLine(status_code) << CRLF; // TODO: check status code

  // Response header
  response_message << "Server: " << "42webserv" << "/1.0" << CRLF;

  response_message << "Date: " << date << CRLF;

  if (!content_type.empty()) {
    response_message << "Content-Type: " << content_type;
    if (!content_charset.empty())
      response_message << "; charset=" << content_charset;
    response_message << CRLF;
  }
  // \rと\0も数えているから見た目（printable + '\n'）より5増える　これでよい？
  response_message << "Content-Length: " << (!error_response_body.empty() ? error_response_body.length() : content_length) << CRLF;
  response_message << "Last-Modified: " << date << CRLF;

  if (!host_data.empty()) {
    response_message << "Location: http";
#if (HTTP_SSL)
    response_message << "s";
#endif
    response_message << "://" << host_data;
    if (http_port != 0)
      response_message << ":" << http_port;
    response_message << location << CRLF;
  }

  if (chunked)
    response_message << "Transfer-Encoding: chunked" << CRLF;
  if (status_code == 101) // switching protocols
    response_message << "Connection: upgrade" << CRLF;
  else if (keep_alive) {
    response_message << "Connection: keep-alive" << CRLF;
    if (!keep_alive_header.empty())
      response_message << "Keep-Alive: timeout=" << keep_alive_header << CRLF;
  } else {
    response_message << "Connection: close" << CRLF;
  }

//  // ETag
//  if (true)
//    response_message << "Accept-Ranges: " << accept_ranges << CRLF;

  // Empty line
  response_message << CRLF;

  // Message Body
  if (status_code >= 300)
    response_message << error_response_body;

  return response_message.str();
}

#include <sys/time.h>

// TODO: REMOVE
// TEST MAIN
//int main() {
//  HttpResponse r;
//
//  for (int i = 200; i < 508; ++i) {
//    if (r.GetResponseMessage(i).find("ERROR NO OUTPUT") == std::string::npos)
//      std::cout << r.GetResponseMessage(i) << std::endl;
//  }
//
//  return 0;
//}