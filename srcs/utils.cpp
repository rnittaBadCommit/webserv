#include "utils.hpp"

 
namespace ft {
    void    CreateFile(const std::string& filePath, const std::string& body) { 
        std::ofstream newFile(filePath.c_str(), std::ofstream::out);
        if (!newFile.good()) {
            throw std::runtime_error("Could not create file");
        }
        newFile << body;
        newFile.close();
    }

    std::set<std::string>    CreateDirectoryList(const std::string& directoryPath) {
        std::set<std::string> dirList;
        struct dirent *dirent_ptr;

        DIR *dir_ptr = opendir(directoryPath.c_str());
        if (dir_ptr == NULL) {
            throw std::runtime_error("Could not open directory");
        }
        while ((dirent_ptr = readdir(dir_ptr))) {
            dirList.insert(dirent_ptr->d_name);
        }
        return (dirList);
        // /dir1/dir2/file
        //l_directoryList.insert(directoryPath);
    }
}
