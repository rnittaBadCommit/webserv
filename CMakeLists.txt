cmake_minimum_required(VERSION 3.16)
project(webserv)

set(CMAKE_CXX_STANDARD 98)

include_directories(socket)
include_directories(srcs)
include_directories(srcs/config)
add_subdirectory(UnitTests)
add_subdirectory(srcs/cgi)
add_subdirectory(srcs/config)
add_subdirectory(srcs/httpMethod)
add_subdirectory(srcs/httpResponse)
add_subdirectory(srcs/HTTP)
add_subdirectory(srcs/server)
add_subdirectory(srcs/utils)

add_executable(webserv

#        main.cpp

#        srcs/socket/server.cpp
#        srcs/socket/server.hpp
#        srcs/socket/socket.cpp
#        srcs/socket/socket.hpp
#        srcs/socket/socket_test.cpp
#        srcs/socket/test.cpp
#        srcs/config/Config.cpp
#        srcs/config/Config.hpp
#        srcs/config/ConfigConstant.hpp
#        srcs/config/ConfigParser.cpp
#        srcs/config/ConfigParser.hpp
#        srcs/config/LocationConfig.cpp
#        srcs/config/LocationConfig.hpp
#        srcs/config/ServerConfig.cpp
#        srcs/config/ServerConfig.hpp

        srcs/httpResponse/HttpResponse.cpp
        srcs/httpResponse/HttpResponse.hpp
        srcs/httpResponse/status_code.hpp

        srcs/httpMethod/HTTPMethod.cpp
        srcs/HTTP/HTTPHead.cpp
        srcs/utils/utils.cpp
        )

target_link_libraries(webserv
        )
