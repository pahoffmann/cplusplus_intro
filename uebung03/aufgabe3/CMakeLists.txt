cmake_minimum_required (VERSION 2.6)
project(SDL)

#Hier den Programmnamen und den Namen der C-Datei einfügen
add_executable(prog prog.c)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2)
