# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (hello_cmake)

# Add an executable
add_executable(some_executable main.cpp)
#add_executable(${PROJECT_NAME} main.cpp)

message(STATUS "MESSAGE 01: ${PROJECT_NAME}")
message(STATUS "MESSAGE 02: ${CMAKE_BINARY_DIR}")