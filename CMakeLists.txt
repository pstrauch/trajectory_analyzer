cmake_minimum_required(VERSION 3.0.0)
project(trajectory_analyzer VERSION 0.1.0)

#build these subdirectories' CMakeLists now
# include_directories(lib/csv_lib) #?
add_subdirectory(lib)
add_subdirectory(app)