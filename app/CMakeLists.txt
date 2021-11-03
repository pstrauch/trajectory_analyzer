#add executable build targets
add_executable(trajectory_analyzer trajectory_analyzer.cpp)

#add libraries
# target_link_libraries(trajectory_analyzer PRIVATE csv_lib)
target_include_directories(trajectory_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)