#add executable build targets
add_executable(trajectory_analyzer trajectory_analyzer.cpp)

#link libraries
target_link_libraries(trajectory_analyzer PRIVATE 
    discretization_lib
    geometric_statistics_lib
    yaml-cpp)

#add includes
target_include_directories(trajectory_analyzer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)