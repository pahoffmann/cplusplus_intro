cmake_minimum_required(VERSION 2.8)
project(SDL2_First)

# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH /UniOsnabrück/c++/C06/uebung03/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(SDL2_App ${SOURCE_FILES})
target_link_libraries(SDL2_App ${SDL2_LIBRARY})
