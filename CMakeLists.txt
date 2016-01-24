cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "-O0 -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -std=c++11")
project (puyo-server)
add_executable(puyo-server src/puyo-server.cpp)
#add_executable(mytest test1.cpp)

