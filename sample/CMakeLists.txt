cmake_minimum_required(VERSION 3.15)
project(debug C)

set(CMAKE_C_STANDARD 11)

add_executable(debug main.c segment_tree.c segment_tree.h)