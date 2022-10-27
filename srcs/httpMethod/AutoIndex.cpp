//
// Created by yuumo on 2022/10/27.
//

#include <string>
#include <sstream>
#include <set>
#include "AutoIndex.hpp"
#include "HTTPMethod.hpp"
#include "httpResponse/HttpResponse.hpp"


std::string get_table_line(std::string path) {
  std::stringstream return_sentence;

  return_sentence << "  <tr>" CRLF
                  << "   <td>" CRLF
                  << "    " << path << CRLF
                  << "   </td>" CRLF
                  << "   <td>" CRLF
                  << "    " << "size" << CRLF
                  << "   </td>" CRLF
                  << "   <td>" CRLF
                  << "    " << "last modified" << CRLF
                  << "   </td>" CRLF
                  << "  </tr>" CRLF;

  return return_sentence.str();
}

std::string render_html(std::set<std::string> dirpath_list) {
  std::stringstream return_sentence;

  return_sentence << "<html>" CRLF
                  << "<head>" CRLF
                  << " <title>" CRLF
                  << "TODO: TITLE" CRLF // TODO: title
                  << " </title>" CRLF
                  << "</head>" CRLF;

  return_sentence << "<body>" CRLF
                  << "<h2>Index of " << "TODO: ROOT DIRPATH" << "</h2>" CRLF;

  return_sentence << "<hr>"  CRLF
                  << "<table>" CRLF
                  << " <thead>" CRLF
                  << "  <tr>" CRLF
                  << "   <th>Name</th>" CRLF
                  << "   <th>Last Modified</th>" CRLF
                  << "   <th>Size</th>" CRLF
                  << "  </tr>" CRLF
                  << " </thead>" CRLF
                  << " <tbody>" CRLF;
  // get table line
  for (std::set<std::string>::iterator iter = dirpath_list.begin(); iter != dirpath_list.end(); ++iter) {
    return_sentence << get_table_line(*iter);
  }
  return_sentence << " </tbody>"  CRLF
                  << "</table>"  CRLF
                  << "</body>"  CRLF
                  << "</html>"  CRLF;

  return return_sentence.str();
}
