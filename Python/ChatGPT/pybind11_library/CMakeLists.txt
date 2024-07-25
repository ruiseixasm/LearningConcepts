cmake_minimum_required(VERSION 3.12)
project(MyLibrary)

# Include directories
include_directories(include)

# Find pybind11
find_package(pybind11 REQUIRED)

# Create the library
pybind11_add_module(my_library src/my_library.cpp)
