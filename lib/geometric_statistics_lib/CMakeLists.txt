add_library(geometric_statistics_lib STATIC 
    geometric_statistics.cpp)

target_include_directories(
    geometric_statistics_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})