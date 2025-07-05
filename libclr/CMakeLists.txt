cmake_minimum_required(VERSION 3.29)
project(libclr VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} SHARED
    ASCII.h
    Block.cpp
    Color.h
    Rect.h
    Screen.cpp
)