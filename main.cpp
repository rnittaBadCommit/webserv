#include <iostream>
#include "./HTTPRequst.hpp"

int main() {
    HTTPRequest     req;
    std::string     line;
    int             rlt = 1;

    while(rlt && std::getline(std::cin, line, '|')) {
        rlt = req.Parse(std::string(line));
    }
    std::cout << "Here is your Request" << std::endl;
    req.PrintRequest();
    return 0;
}
