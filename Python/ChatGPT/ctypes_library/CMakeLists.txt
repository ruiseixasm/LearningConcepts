cmake_minimum_required(VERSION 3.10)
project(MyProject)

# CTYPES DLL LIBRARIES ON WINDOWS HAVE TO BE COMPILED BY VISUAL STUDIO XX
# IF COMPILED BY GCC THOSE FILES WON'T BE RECOGNIZED BY CTYPES AND WILL RESULT IN ERROR

# Include directories
include_directories(include)

# Source files
set(SOURCES src/my_library.cpp)

# Create the shared library
add_library(MyLibrary SHARED ${SOURCES})
# Add the -fPIC option for position-independent code
set_target_properties(MyLibrary PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Specify output directories
set_target_properties(MyLibrary PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
