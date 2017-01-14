project(JUMPER)
 
# States that CMake required version must be greater than 2.6
cmake_minimum_required(VERSION 2.8)
 
# Setup sources
set(STL_SOURCES
    src/Aufgabe2_1.cpp
    src/Aufgabe2_2.cpp
    src/Aufgabe2_3.cpp
    src/STL.cpp
    )

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${STL_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
 

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

# Build executable
add_executable(STL ${STL_SOURCES})
target_link_libraries(STL m)