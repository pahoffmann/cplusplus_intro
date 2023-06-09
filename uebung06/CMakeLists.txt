project(JUMPER)
 
# States that CMake required version must be greater than 2.6
cmake_minimum_required(VERSION 2.8)
 
# Setup sources
set(JUMPER_SOURCES src/MainWindow.cc src/Main.cpp src/Level.cc src/Camera.cc)

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${JUMPER_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
set(CMAKE_CXX_FLAGS "-Wall -Werror ${CMAKE_CXX_FLAGS}")

# Find SDL2 libraries using the custom made module in 
# the cmake/ path
find_package(SDL2 REQUIRED) 
find_package(SDL2_IMAGE REQUIRED) 

# Add SDL2 include directory to search path
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMG_INCLUDE_DIR})

# Build executable
add_executable(jumper ${JUMPER_SOURCES})
target_link_libraries(jumper ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(jumper m)
