#include <iostream>
#include <sstream>
#include <limits>
#include <set>
#include "srcs/HTTP/HTTPHead.hpp"
#include "srcs/utils.hpp"
#include <cerrno>

void    testParser();
void    testUtils();

int main() {
    try {
        testParser();
        //testUtils();
    } catch (const std::exception& e) {
        std::cout << "[exception]: " << e.what() << std::endl;
    }

    return 0;
}

void    testParser() {
    ft::HTTPHead    reqHead;
    std::string     line;
    int             rlt = 1;

    while(rlt && std::getline(std::cin, line, '|')) {
        // how to handle too much body
        //std::cout << "sending:\n" << line << std::endl;
        rlt = reqHead.Parse(std::string(line)); 
    }  
    std::cout << "\n\nBefore" << std::endl;
    reqHead.PrintRequest();

    reqHead.ParseRequestURI();
    
    std::cout << "\nafter\n";
    reqHead.PrintRequest();

}

template <typename T>
void    printContainer(T container) {
    for (typename T::iterator it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}
void testUtils() {
    using namespace std;
    set<std::string> Dir;

    //ft::CreateFile("./ThisFileDoesntExist/", "this will throw an error");
    ft::CreateFile("./nEwFile.txt", "This is the text in nEwFile.txt\n");
    ft::CreateFile("./nEwFile.txt", "and this is the overwrite\n"); 

    //ft::CreateFile("../prevdirfile", "aaaaaaaaaaaaaaawrite\n");
    //ft::CreateFile("/home/aurora/FILE", "aaaaaaaaaaaaaaawrite\n");   
    //ft::CreateFile("/home/aurora/webserv/newDir/newfile", "aaaaaaaaaaaaaaawrite\n");   

    cout << "directory list on doesn't exist dir" << endl;
    Dir = ft::CreateDirectoryList("abc/def/ghi/");
    printContainer(Dir);

    cout << "directory list on this dir relative" << endl;
    Dir = ft::CreateDirectoryList("./");
    printContainer(Dir);

    cout << "directory list on prev dir relative" << endl;
    Dir = ft::CreateDirectoryList("../");
    printContainer(Dir);

    /*cout << "directory list on absolute path" << endl;
    Dir = ft::CreateDirectoryList("/home/aurora/webserv/");
    printContainer(Dir);*/

    /*cout << "throw exception bcs openddir() will return error on trying to open a file" << endl;
    Dir = ft::CreateDirectoryList("/home/aurora/webserv/nEwFile.txt");
    printContainer(Dir);
    */
}
