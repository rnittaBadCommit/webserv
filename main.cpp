#include <iostream>
#include <sstream>
#include <limits>
#include "HTTP/HTTPRequst.hpp"

int main() {
    HTTPRequest     req;
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
    
    std::cout << "Here is your Request" << std::endl;
    req.PrintRequest();
    std::cout << "Here is your Body" << std::endl;
    req.PrintBody();
    return 0;
}
