cmake_minimum_required(VERSION 3.26)
project(FileSorter)

set(CMAKE_CXX_STANDARD 23)

add_executable(FileSorter
        src/main.cpp
        inc/file_sort.h
        src/file_sort.cpp
        inc/file_manager.h
        src/file_manager.cpp)
