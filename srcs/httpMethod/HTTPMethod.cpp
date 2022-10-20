//
// Created by ymori on 2022/10/18.
//

#include "HTTPMethod.hpp"

#include <iostream>

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

int do_http() {

}
