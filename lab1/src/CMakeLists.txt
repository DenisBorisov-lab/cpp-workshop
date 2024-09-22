add_library(solution_library STATIC
        solution.cpp
)

target_include_directories(solution_library PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(lab1 main.cpp)
target_link_libraries(lab1 PRIVATE solution_library)