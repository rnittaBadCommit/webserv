#include "utils.hpp"

namespace ft {
    void    CreateFile(const std::string& file, const std::string& body) { 
        std::ofstream newFile(file.c_str(), std::ofstream::out);
        if (!newFile.good()) {
            throw std::runtime_error("could not open file");
        }
        newFile << body;
        newFile.close();
    }

    /*void    AddPath(const std::string& directoryPath) {
        // /dir1/dir2/file
        l_directoryList.insert(directoryPath);
    }*/
}
