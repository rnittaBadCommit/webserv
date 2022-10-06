#include <iostream>

#include "./HTTPRequst.hpp"
int main() {
    int             rlt = 1;
    std::string     str;
    HTTPRequest     req;

    while (rlt && std::cin >> str) {
       rlt = req.Parse(str);
    }
    return 0;
}
