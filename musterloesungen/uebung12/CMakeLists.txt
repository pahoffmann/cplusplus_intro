project(JUMPER)
 
# States that CMake required version must be greater than 2.6
cmake_minimum_required(VERSION 2.8)
 
# Setup sources
set(JUMPER_SOURCES
    src/Actor.cpp
    src/AnimatedRenderable.cpp
    src/Bot.cpp
    src/Camera.cpp
    src/Collision.cpp
    src/Game.cpp
    src/Item.cpp
    src/Level.cpp
    src/Main.cpp
    src/MainWindow.cpp
    src/Network.cpp
    src/Path.cpp
    src/PathPlanner.cpp
    src/PathFollower.cpp
    src/Player.cpp
    src/PlayerProperty.cpp
    src/Renderable.cpp
    src/ScoreBoard.cpp
    src/StaticRenderable.cpp
    src/TexturedLayer.cpp
    src/TextureFactory.cpp
    src/WorldProperty.cpp
    )

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${JUMPER_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

# Find SDL2 libraries using the custom made module in 
# the cmake/ path
find_package(SDL2 REQUIRED) 
find_package(SDL2_IMAGE REQUIRED) 

# Add SDL2 include directory to search path
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMG_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")

# Build executable
add_executable(jumper ${JUMPER_SOURCES})
target_link_libraries(jumper ${SDL2_LIBRARY} ${SDL2_IMG_LIBRARY})
target_link_libraries(jumper m)