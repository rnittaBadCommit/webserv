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

  return_sentence << " <tbody>" CRLF
                  << "  <tr>" CRLF
                  << "   <td>" CRLF
                  << "    " << path << CRLF
                  << "   </td>" CRLF;
//                  << "   <td>" CRLF
//                  << "    " << "last modified" << CRLF
//                  << "   </td>" CRLF
//                  << "   <td>" CRLF
//                  << "    " << "size" << CRLF
//                  << "   </td>" CRLF
//                  << "  </tr>" CRLF;
  return_sentence << " </tbody>"  CRLF;

  return return_sentence.str();
}

std::string render_html(std::string dirpath_root, std::set<std::string> dirpath_list) {
  std::stringstream return_sentence;

  return_sentence << "<html>" CRLF
                  << "<head>" CRLF
                  << " <title>" CRLF
                  << "Auto index" CRLF
                  << " </title>" CRLF
                  << "</head>" CRLF;

  return_sentence << "<body>" CRLF
                  << "<h2>Index of " << dirpath_root << "</h2>" CRLF;

  return_sentence << "<hr>"  CRLF
                  << "<table>" CRLF
                  << " <thead>" CRLF
                  << "  <tr>" CRLF
                  << "   <th>Name</th>" CRLF
//                  << "   <th>Last modified</th>" CRLF
//                  << "   <th>Size</th>" CRLF
                  << "  </tr>" CRLF
                  << " </thead>" CRLF;

  // get table line
  for (std::set<std::string>::iterator iter = dirpath_list.begin(); iter != dirpath_list.end(); ++iter) {
    // "./" is not printed
    if (*iter == "./")
      continue;
    return_sentence << get_table_line(*iter);
  }

  return_sentence << "</table>"  CRLF
                  << "</body>"  CRLF
                  << "</html>"  CRLF;

  return return_sentence.str();
}
