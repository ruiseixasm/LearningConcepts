cmake_minimum_required(VERSION 3.5)

project(cmake_examples_install)

############################################################
# Create a library
############################################################

# Generate the shared library from the library sources
add_library(cmake_examples_inst SHARED # Shared library (.so)
    src/Hello.cpp
)

target_include_directories(cmake_examples_inst
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(cmake_examples_inst_bin
    src/main.cpp
)

# Link the new hello_library target with the hello_binary target
target_link_libraries(cmake_examples_inst_bin
    PRIVATE
        cmake_examples_inst
)

############################################################
# Install
############################################################

# Binaries          01
install (TARGETS cmake_examples_inst_bin
    DESTINATION bin)

# Library           02
# Note: may not work on windows
install(TARGETS cmake_examples_inst
    LIBRARY DESTINATION lib)

# Header files      03
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include)

# Config            04
install(FILES cmake-examples.conf
    DESTINATION etc)

# This may not work on windows. On platforms that have DLL targets you may need to add the following
# install(TARGETS cmake_examples_inst
#     LIBRARY DESTINATION lib
#     RUNTIME DESTINATION bin)
