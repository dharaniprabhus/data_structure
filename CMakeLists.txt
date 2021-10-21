cmake_minimum_required(VERSION "3.10")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(data_structure)

add_executable(binary_search_tree binary_search_tree.cpp)
add_executable(avl_tree avl_tree.cpp)
