cmake_minimum_required(VERSION 3.10)
project(MusicDataBase)

# Add all source files
file(GLOB SOURCES "lib/*.c" "*.c")

# Specify the executable name
set(EXECUTABLE_NAME "music.out")

# Add the executable target
add_executable(${EXECUTABLE_NAME} ${SOURCES})
