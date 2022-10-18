#include "utils.hpp"

 
namespace ft {
    int     FilePathExists(const std::string& filePath) {
        struct stat             sb;
        return ((stat(filePath.c_str(), &sb) == 0));
    }

    void    MakeLeadingDirectories(std::string& filePath) {
        std::vector<std::string> directories; 
        size_t                  i;
        const unsigned char     delim = '/'; 

        while (!filePath.empty()) {
            i = filePath.find(delim);
            if (i == std::string::npos) {
                directories.push_back(filePath);
                filePath.clear();
            } else {
                directories.push_back(filePath.substr(0, i + sizeof(delim)));
                filePath.erase(0, i + sizeof(delim));
            }
        }
        for (size_t i = 0; i < directories.size() - 1; ++i) {
            filePath += directories[i];
            if (FilePathExists(filePath)) {
                continue ;
            }
            if (mkdir(filePath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
                throw std::runtime_error("Could not create directory");
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
        newFile.open(filePath.c_str(), std::ofstream::out);
        if (!newFile.good()) {
            if (FilePathExists(filePath)) {
                // No write permissions
                throw std::runtime_error("Could not create file");
            }
            MakeLeadingDirectories(filePath);
            newFile.open(filePath.c_str(), std::ofstream::out);
        }
        newFile << body;
        newFile.close();
    }

    std::set<std::string>    CreateDirectoryList(std::string directoryPath) {
        std::set<std::string> dirList;
        struct dirent *dirent_ptr;

        // will include . hidden directories
        // will not throw error in case of create("abc/def")
        if (!FilePathExists(directoryPath)) {
            MakeLeadingDirectories(directoryPath);
            if (mkdir(directoryPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) { 
                throw std::runtime_error("Could not create directory");
            }
        }
        DIR *dir_ptr = opendir(directoryPath.c_str());
        if (dir_ptr == NULL) {
            throw std::runtime_error("Could not open directory");
        }
        while ((dirent_ptr = readdir(dir_ptr))) {
            dirList.insert(dirent_ptr->d_name);
        }
        return (dirList);
    }
}
