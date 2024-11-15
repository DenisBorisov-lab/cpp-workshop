add_subdirectory(lib)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)


add_executable(figure_tests
        tests/figure_tests.cpp
        tests/trapezoid_tests.cpp
        tests/square_tests.cpp
        tests/rectangle_tests.cpp
        tests/point_tests.cpp
        tests/array_tests.cpp
)


target_link_libraries(figure_tests
        PRIVATE
        gtest
        gtest_main
)

target_include_directories(figure_tests
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

add_test(NAME FigureTests COMMAND figure_tests)
