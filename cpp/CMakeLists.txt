cmake_minimum_required(VERSION 3.10)

project(cpp_concurrency)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)

target_include_directories(main PRIVATE include)
