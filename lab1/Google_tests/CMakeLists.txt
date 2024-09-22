add_subdirectory(lib)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_executable(solution_tests solutionTest.cpp)

target_link_libraries(solution_tests
        PRIVATE
        solution_library
        gtest
        gtest_main
)

target_include_directories(solution_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME SolutionTests COMMAND solution_tests)
