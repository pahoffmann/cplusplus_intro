cmake_minimum_required(VERSION 2.6)
PROJECT(TestProject)
 
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
 
QT4_WRAP_UI(UISrcs src/untitled.ui)
QT4_WRAP_CPP(MOCSrcs src/MainWindow.hpp)
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
 
ADD_EXECUTABLE(MyProject src/Main.cpp src/MainWindow.cpp ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(MyProject ${QT_LIBRARIES})




