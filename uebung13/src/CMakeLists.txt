cmake_minimum_required(VERSION 2.6)
PROJECT(TestProject)
 
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
 
QT4_WRAP_UI(UISrcs untitled.ui)
QT4_WRAP_CPP(MOCSrcs MainWindow.hpp LevelScene.hpp GraphicsTileItem.hpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall")
 
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BsINARY_DIR})
 
ADD_EXECUTABLE(MyProject Main.cpp MainWindow.cpp LevelScene.cpp GraphicsTileItem.cpp ${MOCSrcs} ${UISrcs})
TARGET_LINK_LIBRARIES(MyProject ${QT_LIBRARIES})




