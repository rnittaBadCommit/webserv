#pragma once
#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# ifdef __APPLE__
#  define DELIM '\n'
#  define BREAK '\n\n'
# else
#  define DELIM '\r\n'
#  define BREAK '\r\n\r\n'
#endif