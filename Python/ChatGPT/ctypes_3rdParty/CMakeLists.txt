cmake_minimum_required(VERSION 3.15)
project(MyProject)

# Include directories
include_directories(include)

# Source files
set(LIBRARY_SOURCES src/my_library.cpp src/others_library.cpp)

add_library(MyLibrary STATIC ${LIBRARY_SOURCES})
# Add the -fPIC option for position-independent code
set_target_properties(MyLibrary PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Specify output directories
set_target_properties(MyLibrary PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


# Source files
set(CTYPES_SOURCES src/my_library_ctypes.cpp)

add_library(MyLibrary_ctypes SHARED ${CTYPES_SOURCES})
# Link to MyLibrary
target_link_libraries(MyLibrary_ctypes PRIVATE MyLibrary)
# Add the -fPIC option for position-independent code
set_target_properties(MyLibrary_ctypes PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Specify output directories
set_target_properties(MyLibrary_ctypes PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


# Source files
set(EXECUTABLE_SOURCES main.cpp src/my_library.cpp)

# Specify the executable name
if (WIN32) # LINUX is new for CMake VERSION 3.25
    set(EXECUTABLE_NAME "MyExecutalbe")
else()
    set(EXECUTABLE_NAME "MyExecutable.out")
endif()

# Add the executable target
add_executable(${EXECUTABLE_NAME} ${EXECUTABLE_SOURCES})
# Link to MyLibrary
target_link_libraries(${EXECUTABLE_NAME} PRIVATE MyLibrary)

