cmake_minimum_required(VERSION 3.17)
project(parallel_sorts)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenMP REQUIRED)

add_executable(quick_sort main.cpp domain.h helper.h)

target_link_libraries(quick_sort PRIVATE OpenMP::OpenMP_CXX)