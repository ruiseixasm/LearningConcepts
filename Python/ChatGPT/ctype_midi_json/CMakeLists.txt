cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Include directories
include_directories(include single_include)


# Source files
set(LIBRARY_SOURCES src/my_library.cpp src/RtMidi.cpp)

set(LIBRARY_NAME "MyLibrary")
add_library(${LIBRARY_NAME} STATIC ${LIBRARY_SOURCES})
# Add the -fPIC option for position-independent code
set_target_properties(${LIBRARY_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Specify output directories
set_target_properties(${LIBRARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


# Source files
set(CTYPES_SOURCES src/my_library_ctypes.cpp)

add_library(MyLibrary_ctypes SHARED ${CTYPES_SOURCES})
# Link to MyLibrary
target_link_libraries(MyLibrary_ctypes PRIVATE ${LIBRARY_NAME})
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
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})

# Check if we are on Windows
if (WIN32)  # Try to load ASIO SDK
    add_compile_definitions(__WINDOWS_MM__)
    target_link_libraries(${LIBRARY_NAME} PRIVATE
            winmm.lib
            ws2_32.lib
            wininet.lib
            version.lib
            Shlwapi.dll
        )
else()
    # Find and link ALSA library
    find_package(ALSA REQUIRED)
    if (ALSA_FOUND)
        include_directories(${ALSA_INCLUDE_DIRS})
        target_link_libraries(${LIBRARY_NAME} PRIVATE
            ${ALSA_LIBRARIES}
            pthread
            asound
        )
        add_definitions(-D__LINUX_ALSA__)
    endif()
endif()
