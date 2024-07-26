cmake_minimum_required(VERSION 3.12)
project(MyLibrary)

include_directories(include)

# Set pybind11 directory (the path should be to the share/cmake/pybind11 directory)
# IT HAS TO BE THE FULL PATH TO "pybind11Config.cmake"
set(pybind11_DIR "C:/Python311/Lib/site-packages/pybind11/share/cmake/pybind11")

# Find the pybind11 package (DOESN'T TRY TO FIND IT IN SUBDIRECTORIES!!)
find_package(pybind11 REQUIRED)

# Include the pybind11 headers
include_directories(${pybind11_INCLUDE_DIRS})

# Create the pybind11 module
pybind11_add_module(my_library src/my_library.cpp)

if(WIN32)
    target_compile_definitions(my_library PRIVATE BUILDING_DLL=1)
endif()