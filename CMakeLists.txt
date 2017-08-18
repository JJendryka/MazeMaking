cmake_minimum_required(VERSION 3.7)
project(Maze)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BMPHelper.cpp BMPHelper.h Variables.h MazeRecursiveBacktracker.cpp MazeRecursiveBacktracker.h)
add_executable(Maze ${SOURCE_FILES})