cmake_minimum_required(VERSION 3.20)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Minesweeper
        baseheader.cpp
        baseheader.h
        gamer.cpp
        gamer.h
        main.cpp
        timer.cpp
        timer.h)
