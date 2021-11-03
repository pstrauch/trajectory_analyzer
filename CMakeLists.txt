cmake_minimum_required(VERSION 3.0.0)
project(trajectory_analyzer VERSION 0.1.0)

#find installed packages
find_package(yaml-cpp CONFIG REQUIRED)

#build these subdirectories' CMakeLists
add_subdirectory(lib)
add_subdirectory(app)