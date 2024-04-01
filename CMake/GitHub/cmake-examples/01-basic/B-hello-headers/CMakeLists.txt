# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello_headers)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/Hello.cpp
    src/main.cpp
)

# Add an executable with the above sources
add_executable(hello_headers ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(hello_headers
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include    
)

# Print Directory Paths
message(STATUS "MESSAGE 01 CMAKE_SOURCE_DIR:            ${CMAKE_SOURCE_DIR}")
message(STATUS "MESSAGE 02 CMAKE_CURRENT_SOURCE_DIR:    ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "MESSAGE 03 PROJECT_SOURCE_DIR:          ${PROJECT_SOURCE_DIR}")
message(STATUS "MESSAGE 04 CMAKE_BINARY_DIR:            ${CMAKE_BINARY_DIR}")
message(STATUS "MESSAGE 05 CMAKE_CURRENT_BINARY_DIR:    ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "MESSAGE 06 PROJECT_BINARY_DIR:          ${PROJECT_BINARY_DIR}")
