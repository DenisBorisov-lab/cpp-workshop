add_subdirectory(lib)

set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

add_executable(hex_tests hexTest.cpp)

target_link_libraries(hex_tests
        PRIVATE
        hex_library
        gtest
        gtest_main
)

target_include_directories(hex_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_test(NAME HexTests COMMAND hex_tests)
