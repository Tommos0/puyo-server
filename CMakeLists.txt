cmake_minimum_required (VERSION 2.6)

IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
    message("Target = DEBUG")
    add_definitions(-DDEBUG)
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
IF(CMAKE_BUILD_TYPE MATCHES RELEASE)
    message("Target = RELEASE")
ENDIF(CMAKE_BUILD_TYPE MATCHES RELEASE)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -fdiagnostics-color=auto")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -ggdb ")
set(CMAKE_CXX_FLAGS_RELEASE "-g0 -O3 ")
set(CMAKE_VERBOSE_MAKEFILE ON)
project (puyo-server)
#add_subdirectory(src)
file(GLOB all_src
        "src/*.h"
        "src/*.cpp"
    )
add_executable(puyo-server ${all_src}) 
set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS system REQUIRED) 
include_directories(${Boost_INCLUDE_DIRS}) 
target_link_libraries(puyo-server ${Boost_LIBRARIES})

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses) 
if (CURSES_FOUND)
    message("Curses found: ${CURSES_LIBRARIES}")
    add_definitions(-DCURSES)
    include_directories(${CURSES_INCLUDE_DIR}) 
    target_link_libraries(puyo-server ${CURSES_LIBRARIES})
endif (CURSES_FOUND)

