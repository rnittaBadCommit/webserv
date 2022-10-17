#pragma once
#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <fstream>
# include <istream>
#include <set>
#include <sys/types.h>
#include <dirent.h>

namespace ft {
    void                    CreateFile(const std::string& file, const std::string& body);
    std::set<std::string>   CreateDirectoryList(const std::string& directoryPath);
}

#endif