cmake_minimum_required(VERSION 3.6)
project(4_processor)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp processor.h commands.h registers.h file_buffer.h asssembler.h)
add_executable(4_processor ${SOURCE_FILES})