cmake_minimum_required(VERSION 3.0)
include(CheckCXXCompilerFlag)

project(yatbcpp_hello_user)


CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "-std=c++17")
    message(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has C++17 support. It is now enabled.")
elseif(COMPILER_SUPPORTS_CXX1Z)
    set(CMAKE_CXX_FLAGS "-std=c++1z")
    message(STATUS "The Compiler ${CMAKE_CXX_COMPILER} has experimental C++17 support. It is now enabled.")
else()
    message(FATAL_ERROR "The Compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ Compiler")
endif()

SET(BUILD_SHARED_LIBRARIES OFF)

find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(Threads REQUIRED)
find_package(yatbcpp REQUIRED)

set(SOURCE_FILES main.cpp)
add_executable(yatbcpp_hello_user ${SOURCE_FILES})
target_link_libraries(yatbcpp_hello_user ${YATBCPP_LIBRARIES} jsoncpp ${CURL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})