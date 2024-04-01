cmake_minimum_required(VERSION 3.5)

project(hello_library)


############################################################
# Create a library
############################################################

# Generate the shared library from the library sources
add_library(hello_library SHARED # Where the library is defined as shared instead of static
    src/Hello.cpp
)

add_library(hello::library ALIAS hello_library)

target_include_directories(hello_library
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)


############################################################
# Create an executable
############################################################

# Add an executable with the above sources (make sure it's hello_binary and not hello_library)
add_executable(hello_binary
    src/main.cpp
)

# Link the new hello_library target with the hello_binary target
target_link_libraries(hello_binary
    PRIVATE
        hello::library
)


# Same as calling the followinf command
# /usr/bin/c++ CMakeFiles/hello_binary.dir/src/main.cpp.o -o hello_binary -rdynamic libhello_library.so -Wl,-rpath,/home/matrim/workspace/cmake-examples/01-basic/D-shared-library/build
