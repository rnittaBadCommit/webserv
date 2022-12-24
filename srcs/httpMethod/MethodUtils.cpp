//
// Created by ymori on 2022/10/20.
//

#include "MethodUtils.hpp"

/**
 *
 * @param szUri
 * @param is_cgi
 * @return
 *
 * @brief
 */
std::string get_uri_and_check_CGI(const std::string &szUri, std::string &query_string, bool &is_cgi) {

  std::string uri;

  std::string::size_type urlPos = szUri.rfind('?');
  if (urlPos != std::string::npos) {
    uri = szUri.substr(0, urlPos);
    if (urlPos + 1 != szUri.length()) { // ? only
      std::string query = szUri.substr(++urlPos);
      if (query.rfind('=') != std::string::npos) {
        query_string = query;
        is_cgi = true;
      }
    }
  } else {
    uri = szUri;
  }

  return uri;
}