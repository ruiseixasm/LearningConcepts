project(MyApp)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source files for the executable
set(SRC_SOURCES main.cpp)

# Create the executable
add_executable(MyApp ${SRC_SOURCES})

# Link the executable with the library
target_link_libraries(MyApp MyLibrary)

# Include the directory where my_library.hpp is located
target_include_directories(MyApp PRIVATE ${CMAKE_SOURCE_DIR}/lib)
