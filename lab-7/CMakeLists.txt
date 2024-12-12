cmake_minimum_required(VERSION 3.10)
project(lab7)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.15.2
        TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES false src/*.cpp)
add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

add_executable(${CMAKE_PROJECT_NAME}_exe main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/headers)

target_link_libraries(${CMAKE_PROJECT_NAME}_exe PRIVATE ${CMAKE_PROJECT_NAME}_lib)

enable_testing()

add_executable(tests_lab tests/test.cpp)
target_include_directories(tests_lab PUBLIC ${CUR_PR}/headers)
target_link_libraries(tests_lab ${CMAKE_PROJECT_NAME}_lib gtest_main)

add_test(NAME MyProjectTests COMMAND tests_lab)