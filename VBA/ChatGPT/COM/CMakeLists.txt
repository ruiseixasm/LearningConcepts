cmake_minimum_required(VERSION 3.10)
project(RandomNumberCOM)

set(SOURCES RandomNumberCOM.cpp)

#add_definitions(-DREGISTER_COM_DLL)

add_library(RandomNumberCOM SHARED ${SOURCES})

# Define export macros
target_compile_definitions(RandomNumberCOM PRIVATE EXPORT_COM_DLL)

# Set the output directory
set_target_properties(RandomNumberCOM PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Release"
)