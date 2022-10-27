project(Google_Tests)

add_subdirectory(lib/googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# add Test files
add_executable(Google_Tests_run
        HttpMethodTests.cpp
        HttpRequestTests.cpp
        UtilsTests.cpp
        )

target_link_libraries(Google_Tests_run
        httpMethod
        httpResponse
        httpRequest
        utils
        )

target_link_libraries(Google_Tests_run
        gtest
        gtest_main)