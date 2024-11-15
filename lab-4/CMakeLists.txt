cmake_minimum_required(VERSION 3.10)
project(lab4 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Google_tests)

add_executable(lab4 main.cpp)
target_include_directories(lab4 PRIVATE include)

enable_testing()