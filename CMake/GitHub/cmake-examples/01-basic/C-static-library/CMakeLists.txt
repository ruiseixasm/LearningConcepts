cmake_minimum_required(VERSION 3.5)

project(hello_library)

############################################################
# Create a library
############################################################

# Generate the static library from the library sources
add_library(hello_library STATIC
    src/Hello.cpp
)

target_include_directories(hello_library
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include # inluded as '#include "static/Hello.h"' in Hello.cpp and main.cpp
)

############################################################
# Create an executable (Linking a Library)
############################################################

# Add an executable with the above sources (it's hello_binary NOT hello_library)
add_executable(hello_binary
    src/main.cpp
)

# Link the new hello_library target with the hello_binary target
target_link_libraries(hello_binary
    PRIVATE
        hello_library
)