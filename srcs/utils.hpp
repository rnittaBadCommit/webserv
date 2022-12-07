#pragma once
#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <fstream>
# include <istream>
# include <set>
# include <vector>
# include <sys/types.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

namespace ft {
    void                    CreateFile(std::string file, const std::string& body);
    std::set<std::string>   CreateDirectoryList(std::string directoryPath);
    void                    TrimWSP(std::string& str);
   	unsigned int	        StrBase_to_UI_(const std::string& str, std::ios_base& (*base)(std::ios_base&));
   	int	                    StrBase_to_I_(const std::string& str, std::ios_base& (*base)(std::ios_base&));
}

#endif