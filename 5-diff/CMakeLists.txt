cmake_minimum_required(VERSION 3.6)
project(5_diff)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp parseer.h simplifier.h tree.h printer.h)
add_executable(5_diff ${SOURCE_FILES})