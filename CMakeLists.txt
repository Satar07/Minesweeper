cmake_minimum_required(VERSION 3.19)
project(gamer)

set(CMAKE_CXX_STANDARD 14)

add_executable(gamer main.cpp gamer.cpp gamer.h baseheader.cpp baseheader.h timer.cpp timer.h)