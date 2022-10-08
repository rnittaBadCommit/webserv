#pragma once
#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# ifdef _WIN32 || _WIN64 || __MINGW32__ || __MINGW32__ || __MINGW64
#  define DELIM '\r\n'
#  define BREAK '\r\n\r\n'
# else
#  define DELIM '\n'
#  define BREAK '\n\n'
#endif