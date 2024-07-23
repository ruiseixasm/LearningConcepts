project(MyLibrary)

# Set the output directory for the shared library
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files for the library
set(SRC_SOURCES my_library.cpp)

# Create the shared library
add_library(MyLibrary SHARED ${SRC_SOURCES})

# Set properties for Windows DLL export
if(WIN32)
    target_compile_definitions(MyLibrary PRIVATE -DBUILDING_DLL)
endif()
