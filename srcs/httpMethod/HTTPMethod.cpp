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
  
}
