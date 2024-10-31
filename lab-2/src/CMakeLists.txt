add_library(hex_library STATIC
        hex.cpp
)

target_include_directories(hex_library PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(lab2 main.cpp)
target_link_libraries(lab2 PRIVATE hex_library)