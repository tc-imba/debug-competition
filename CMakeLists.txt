cmake_minimum_required(VERSION 3.15)
project(debug)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_executable(debug sample/main.c sample/segment_tree.c sample/segment_tree.h)
add_executable(debug_cpp sample/main.cpp)
add_executable(debug_test sample/test.cpp sample/segment_tree.c sample/segment_tree.h)
add_executable(debug_generate sample/generate.cpp)
