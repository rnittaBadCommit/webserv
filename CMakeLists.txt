cmake_minimum_required(VERSION 3.23)
Project(webserv)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(UnitTests)
add_subdirectory(srcs/httpMethod)

add_executable(webserv
        main.cpp
#        httpmain.cpp
        srcs/httpMethod/HTTPMethod.cpp
        )

target_link_libraries(webserv
        )
