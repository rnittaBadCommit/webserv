//
// Created by ymori on 2022/10/20.
//

#include "MethodUtils.hpp"

#include <iostream>

std::string get_uri(std::string &szUri) {

  bool is_cgi = false;
  std::string uri;

  std::string::size_type urlPos = szUri.rfind('?');
  if (urlPos != std::string::npos) {
    uri = szUri.substr(0, urlPos);
    if (urlPos + 1 != szUri.length()) { // ? only
      std::string query = szUri.substr(++urlPos);
      if (query.rfind('=') != std::string::npos)
        is_cgi = true;
    }
  } else {
    uri = szUri;
  }

  return uri;
}