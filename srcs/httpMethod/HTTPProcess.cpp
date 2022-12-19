//
// Created by ymori on 22/12/17.
//

#include <string>

#include "HTTPMethod.hpp"
#include "MethodUtils.hpp"

/**
 *
 * @param server_child
 * @return
 *
 * @author ymori
 *
 */
std::string http_process(ft::ServerChild server_child) {
  std::string response_message_str;

  /*
   * Get information from ServerChild
   */
  const std::string kRequestMethod = server_child.Get_HTTPHead().GetRequestMethod();
  const std::string kFilePath = server_child.Get_path();
  const std::string kHttpBody = server_child.Get_body();

  /*
   * TODO: Check if CGI should be executed.
   * If URI contains CGI-path defined in the config file and the request method is POST or GET,
   * then execute CGI.
   */
  bool is_CGI = false;
  std::string plane_filepath = get_uri_and_check_CGI(kFilePath, is_CGI);

  // TODO: delete. for debug
  std::cerr << "*************************" << std::endl;
  std::cerr << "server_child.Get_path(): " << kFilePath << std::endl;
  std::cerr << "plane_filepath:          " << plane_filepath << std::endl;
  std::cerr << "*************************" << std::endl;
  // ***

  if (kRequestMethod == "POST") {
    // Any POST request is CGI
    do_CGI(server_child, response_message_str, std::string());
  } else if (kRequestMethod == "GET") {
    if (is_CGI) {
      do_CGI(server_child, response_message_str, plane_filepath);
    } else {
      do_get(plane_filepath, response_message_str);
    }
  } else if (kRequestMethod == "PUT") {
    do_put(kHttpBody, plane_filepath, response_message_str);
  } else if (kRequestMethod == "DELETE") {
    do_delete(plane_filepath, response_message_str);
  } else {
    disallow_method(response_message_str);
  }

  return response_message_str;
}
