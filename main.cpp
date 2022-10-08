#include <iostream>
#include "./HTTPRequst.hpp"
//ifmac \r if unix \r\n

int main() {
    HTTPRequest     req;
    std::string     line;
    int             rlt = 1;

    while(rlt && std::getline(std::cin, line, '|')) {
        rlt = req.Parse(std::string(line));
        // if httprequest is complete &&
    }
    std::cout << "Request" << std::endl;
    req.PrintRequest();


    std::cout << "DONE" << std::endl;
    return 0;
}
