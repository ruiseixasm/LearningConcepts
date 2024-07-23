cmake_minimum_required(VERSION 3.10)
project(MyProject)

# Include directories
include_directories(include single_include)

# Set properties for Windows DLL export
if(WIN32)
    add_compile_definitions(__WINDOWS_MM__)
endif()

# Add all source files from the src directory
file(GLOB SRC_SOURCES "src/*.cpp")

set(LIBRARY_NAME "MyLibrary")
add_library(${LIBRARY_NAME} STATIC ${SRC_SOURCES})

# Set properties for Windows DLL export
if(WIN32)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE -DBUILDING_DLL)
endif()

# Specify output directories
set_target_properties(${LIBRARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


set(LIBRARY_CTYPES "MyLibrary_ctypes")
add_library(${LIBRARY_CTYPES} SHARED ${SRC_SOURCES})

# Link to MyLibrary
target_link_libraries(${LIBRARY_CTYPES} PRIVATE ${LIBRARY_NAME})

# Specify output directories
set_target_properties(${LIBRARY_CTYPES} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)


# Source files
set(SOURCES main.cpp)

# Combine all sources
list(APPEND SOURCES ${LIBRARY_SOURCES})

# Specify the executable name
if (WIN32) # LINUX is new for CMake VERSION 3.25
    set(EXECUTABLE_NAME "MyExecutalbe")
else()
    set(EXECUTABLE_NAME "MyExecutable.out")
endif()

# Add the executable target
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link to MyLibrary
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})

# Check if we are on Windows
if (WIN32)  # Try to load ASIO SDK
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
