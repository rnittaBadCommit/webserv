#include <iostream>
#include <sstream>
#include <limits>
#include "srcs/HTTP/HTTPRequst.hpp"

int main() {
    ft::HTTPRequest     req(8000);
    std::string     line;
    int             rlt = 1;

    try {
        while(rlt && std::getline(std::cin, line, '|')) {
            // how to handle too much body
            //std::cout << "sending:\n" << line << std::endl;
            rlt = req.Parse(std::string(line)); 
        }
    } catch (const std::exception& e) {
        std::cout << "[exception]: " << e.what() << std::endl;
    }
    
    std::cout << "\n\nHere is your Request" << std::endl;
    req.PrintRequest();
    req.PrintBody();
    return 0;
}
