cmake_minimum_required(VERSION 3.10)
project(MusicDataBase)

# Add all source files
file(GLOB SOURCES "lib/*.c" "*.c")

# Specify the executable name
set(EXECUTABLE_NAME "music.out")

# Add the executable target
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Set the build type to "Debug"
set(CMAKE_BUILD_TYPE Debug)

# Add compiler flags for debugging
target_compile_options(${EXECUTABLE_NAME} PRIVATE -g)

# Disable optimization for debug builds
target_compile_options(${EXECUTABLE_NAME} PRIVATE -O0)
