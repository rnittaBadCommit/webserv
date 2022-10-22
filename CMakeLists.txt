cmake_minimum_required(VERSION 3.16)
project(webserv)

set(CMAKE_CXX_STANDARD 98)

include_directories(socket)
include_directories(srcs)
include_directories(srcs/config)
add_subdirectory(UnitTests)
add_subdirectory(srcs/httpMethod)

add_executable(webserv
        socket/main.cpp
        socket/server.cpp
        socket/server.hpp
        socket/socket.cpp
        socket/socket.hpp
        socket/socket_test.cpp
        socket/test.cpp
        srcs/config/Config.cpp
        srcs/config/Config.hpp
        srcs/config/ConfigConstant.hpp
        srcs/config/ConfigParser.cpp
        srcs/config/ConfigParser.hpp
        srcs/config/LocationConfig.cpp
        srcs/config/LocationConfig.hpp
        srcs/config/ServerConfig.cpp
        srcs/config/ServerConfig.hpp
        srcs/httpResponse/HttpResponse.cpp
        srcs/httpResponse/HttpResponse.hpp
        srcs/httpResponse/status_code.hpp

        srcs/httpMethod/HTTPMethod.cpp
        )

target_link_libraries(webserv
        )
