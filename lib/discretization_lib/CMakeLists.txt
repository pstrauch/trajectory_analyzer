add_library(discretization_lib STATIC 
    src/circle.cpp
    src/line.cpp)

target_include_directories(
    discretization_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})