cmake_minimum_required(VERSION 3.15)
project(debug)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


add_executable(debug_generate sample/generate.cpp)

add_compile_options(-g -fsanitize=address -fno-omit-frame-pointer)

add_library(debug_segment_tree_c sample/segment_tree.c sample/segment_tree.h)
add_library(debug_segment_tree_cpp sample/segment_tree.cpp sample/segment_tree.h)
target_link_libraries(debug_segment_tree_c asan ubsan)
target_link_libraries(debug_segment_tree_cpp asan ubsan)

add_executable(debug_c sample/main.c)
target_link_libraries(debug_c debug_segment_tree_c asan ubsan)

add_executable(debug_cpp sample/main.cpp)
target_link_libraries(debug_cpp debug_segment_tree_cpp asan ubsan)

add_executable(debug_test_cpp sample/test.cpp)
target_link_libraries(debug_test_cpp debug_segment_tree_cpp asan ubsan)

add_compile_options(-DDEBUG_C)
add_executable(debug_test_c sample/test.cpp)
target_link_libraries(debug_test_c debug_segment_tree_c asan ubsan)

