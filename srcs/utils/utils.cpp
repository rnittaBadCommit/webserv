#include "utils.hpp"
#include <cerrno>
#include <cstring>

namespace ft {
    int     PathExists(const std::string& filePath) {
        struct stat sb;
        return (stat(filePath.c_str(), &sb) == 0);
    }

    bool    PathIsDir(const std::string& filePath) {
        struct stat sb;

        if (stat(filePath.c_str(), &sb) == -1) {
            throw std::runtime_error("Error while checking Path: " + std::string(strerror(errno)));
        }
        return (S_ISDIR(sb.st_mode));
    }

    void    MakeLeadingDirectories(std::string& filePath) {
        std::vector<std::string> directories; 
        size_t                  i;
        const unsigned char     delim = '/'; 

        //split filepath by delimiter into 'directories'
        while (!filePath.empty()) {
            i = filePath.find(delim);
            if (i != std::string::npos) {
                directories.push_back(filePath.substr(0, i + sizeof(delim)));
                filePath.erase(0, i + sizeof(delim));
            } else {
                directories.push_back(filePath);
                filePath.clear();
            }
        }
        // reconnect path part by part and create filePath's leading directories if they don't exist
        for (size_t i = 0; i < directories.size() - 1; ++i) {
            filePath += directories[i];
            if (!PathExists(filePath)) {
                // only proceed if the error is ENOENT "no such file or directory"
                if (errno != ENOENT) {
                    throw std::runtime_error("Error while checking Path: " + std::string(strerror(errno)));
                }
                if (mkdir(filePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
                  throw std::runtime_error("Could not create directory");
                } 
            }
        }
        filePath += directories.back();
    }

    void    CreateFile(std::string filePath, const std::string& body) { 
        std::ofstream           newFile;

        if (filePath[filePath.size() - 1] == '/') {
            // filepath leads to directory
            throw std::runtime_error("No file selected");
        }
        // try to open file for body writing
        newFile.open(filePath.c_str(), std::ofstream::out);
        if (!newFile.good()) { 
            if (!PathExists(filePath)) {
                // only proceed if the error is ENOENT "no such file or directory"
                if (errno != ENOENT) {
                    throw std::runtime_error("Error while checking Path: " + std::string(strerror(errno)));
                }
                MakeLeadingDirectories(filePath);
                newFile.open(filePath.c_str(), std::ofstream::out);
                if (!newFile.good()) {
                    throw std::runtime_error("Could not create file");
                }
            } else {
                // No write permissions
                throw std::runtime_error("Could not open file");
            }
        }
        newFile << body;
        newFile.close();  
    }

    std::set<std::string>    CreateDirectoryList(std::string directoryPath) {
        std::set<std::string>   dirList;
        struct dirent           *dirent_ptr;
        std::string             fileName;

        if (!PathExists(directoryPath)) {
            /*maybe throw in case dir path is invalid - throw std::runtime_error("Could not create directory");*/
            // only proceed if the error is ENOENT "no such file or directory"
            if (errno != ENOENT) {
                throw std::runtime_error("Error while checking Path: " + std::string(strerror(errno)));
            }
            MakeLeadingDirectories(directoryPath);
            if (mkdir(directoryPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) { 
                throw std::runtime_error("Could not create directory");
            }
        }

        DIR *dir_ptr = opendir(directoryPath.c_str());
        if (dir_ptr == NULL) {
            throw std::runtime_error("Could not open directory");
        }

        // reset errno for checking if readdir resulted in an error
        errno = 0;
        while ((dirent_ptr = readdir(dir_ptr))) {
            fileName = std::string(dirent_ptr->d_name);

            if (PathIsDir(directoryPath + fileName)) {
                fileName += '/';
            }
            dirList.insert(fileName); 
        }
        if (errno != 0) {
            throw std::runtime_error("Error while reading dir contents: " + std::string(strerror(errno)));
        }
        return (dirList);
    }

    void    TrimWSP(std::string& str) {
        while (str.size() && isspace(str[0])) {
            str.erase(0, 1);
        }
        while (str.size() && isspace(str[str.size() - 1])) {
            str.erase(str.size() - 1, 1);
        }
    }
}
