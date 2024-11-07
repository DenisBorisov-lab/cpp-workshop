add_library(figure_library STATIC
        figure.cpp
        triangle.cpp
        square.cpp
        rectangle.cpp
        figureArray.cpp
        trapezoid.cpp
)

target_include_directories(figure_library PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(lab3 main.cpp)
target_link_libraries(lab3 PRIVATE figure_library)