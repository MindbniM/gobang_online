cmake_minimum_required(VERSION 3.20)
project(web)

set(CMAKE_C_COMPILER "/usr/bin/gcc-11")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-11")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_SOURCE_DIR}/util)
include_directories(${CMAKE_SOURCE_DIR}/module)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
find_package(jsoncpp REQUIRED)
set(MySQL_INCLUDE_DIR "/usr/include/mysql/")
set(MySQL_LIBRARIES "/usr/lib/x86_64-linux-gnu/libmysqlclient.so")

include_directories(${MySQL_INCLUDE_DIR})

add_executable(test test.cpp)
target_link_libraries(test Threads::Threads ${MySQL_LIBRARIES} jsoncpp)