cmake_minimum_required(VERSION 3.10)
project(Program4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp MyString.cpp Project4.cpp)
add_executable(Project4 ${SOURCE_FILES})
