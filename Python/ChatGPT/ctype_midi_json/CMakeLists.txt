cmake_minimum_required(VERSION 3.10)
project(MyLibrary)

# Include directories
include_directories(include)

# Set properties for Windows DLL export
if(WIN32)
    add_compile_definitions(__WINDOWS_MM__)
endif()

# Source files
set(RTMIDI_SOURCES src/RtMidi.cpp)
set(LIBRARY_SOURCES src/my_library.cpp)

set(LIBRARY_NAME "MyLibrary_ctypes")
# Create the shared library
add_library(RtMidiLib SHARED ${RTMIDI_SOURCES})
add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})

# Set properties for Windows DLL export
if(WIN32)
    target_compile_definitions(${LIBRARY_NAME} PRIVATE -DBUILDING_DLL)
endif()

# Link RtMidiLib with MyLibrary
target_link_libraries(${LIBRARY_NAME} RtMidiLib)

# Specify output directories
set_target_properties(RtMidiLib PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)
set_target_properties(${LIBRARY_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Source files
set(SOURCES main.cpp)

# Combine all sources
list(APPEND SOURCES ${LIBRARY_SOURCES})

# Specify the executable name
if (WIN32) # LINUX is new for CMake VERSION 3.25
    set(EXECUTABLE_NAME "MidiJsonPlayer")
else()
    set(EXECUTABLE_NAME "MidiJsonPlayer.out")
endif()

# Add the executable target
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link to MyLibrary
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBRARY_NAME})

# Check if we are on Windows
if (WIN32)  # Try to load ASIO SDK
    target_link_libraries(RtMidiLib PRIVATE
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
        target_link_libraries(RtMidiLib PRIVATE
            ${ALSA_LIBRARIES}
            pthread
            asound
        )
        add_definitions(-D__LINUX_ALSA__)
    endif()
endif()
