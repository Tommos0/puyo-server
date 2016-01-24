cmake_minimum_required (VERSION 2.6)
set(CMAKE_CXX_FLAGS "-O0 -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -std=c++11")
project (puyo-server)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

find_package(Boost COMPONENTS system REQUIRED) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    add_executable(progname puyo-server src/puyo-server) 
    target_link_libraries(progname ${Boost_LIBRARIES})
endif()
