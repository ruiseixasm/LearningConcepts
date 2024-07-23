cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/my_library.cpp
)

# Create the shared library
add_library(MyLibrary SHARED ${SOURCES})

# Set properties for Windows DLL export
if(WIN32)
    target_compile_definitions(MyLibrary PRIVATE -DBUILDING_DLL)
endif()

# Specify output directories
set_target_properties(MyLibrary PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
