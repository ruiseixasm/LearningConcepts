cmake_minimum_required(VERSION 3.10)

# Project name
project(RandomNumberDLL)

# Set the output directory for the DLL
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Specify the source files
set(SOURCES RandomNumber.cpp)

# Add the library
add_library(RandomNumberDLL SHARED ${SOURCES})

# Define the Windows DLL export symbol (for __declspec(dllexport))
target_compile_definitions(RandomNumberDLL PRIVATE RANDOM_NUMBER_DLL_EXPORTS)

# Specify the output name of the DLL
set_target_properties(RandomNumberDLL PROPERTIES OUTPUT_NAME "RandomNumber")

# Ensure the compiler treats the code as position-independent (required for shared libraries)
set_target_properties(RandomNumberDLL PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Include directories if needed (adjust path as necessary)
# target_include_directories(RandomNumberDLL PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Linker flags (optional, if additional dependencies are required)
# target_link_libraries(RandomNumberDLL PRIVATE SomeLibrary)

# Debugging options (optional)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(RandomNumberDLL PRIVATE DEBUG)
    target_compile_options(RandomNumberDLL PRIVATE -g)
endif()
