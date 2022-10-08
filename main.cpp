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
    std::cout << "Here is your Request" << std::endl;
    req.PrintRequest();
    return 0;
}
