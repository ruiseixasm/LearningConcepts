cmake_minimum_required(VERSION 3.5)

# Set a default C++ compile flag
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE)
#set(CMAKE_CXX_FLAGS "-DEX2" CACHE STRING "Set C++ Compiler Flags" FORCE) # avoids adding "-DEX2" for each build
#set(CMAKE_CXX_FLAGS "-DEX2") # https://cmake.org/cmake/help/v3.0/command/set.html
#set(CMAKE_CXX_FLAGS "-DEX2" CACHE STRING "Set C++ Compiler Flags") # Only has an effect if the variable isn't already in the cache

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2") # The correct way to do it, non-cache variables! (Page 121)

# Set the project name
project(compile_flags)

# Add an executable
add_executable(cmake_examples_compile_flags main.cpp)

target_compile_definitions(cmake_examples_compile_flags # Prefered method of setting compiler flags
    PRIVATE EX3
)

# Print Directory Paths
message(STATUS "MESSAGE 01 CMAKE_CXX_FLAGS:         ${CMAKE_CXX_FLAGS}")
