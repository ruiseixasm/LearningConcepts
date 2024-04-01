cmake_minimum_required(VERSION 3.5)

# Set the project name
project(third_party_include)

# Make sure Boost library is installed first
# $ dpkg -l | grep boost or $ apt list | grep libboost-all-dev
# need to find "libboost-all-dev", if not, then install it with the command bellow
# $ sudo apt install libboost-all-dev

# Print Directory Paths
message(STATUS "MESSAGE 01 CMAKE_MODULE_PATH:            ${CMAKE_MODULE_PATH}")
message(STATUS "MESSAGE 02 Boost_INCLUDE_DIR:            ${Boost_INCLUDE_DIR}")

# Find a boost install with the libraries filesystem and system
find_package(Boost 1.46.1 REQUIRED COMPONENTS filesystem system)

# -- Found Boost: /usr/lib/x86_64-linux-gnu/cmake/Boost-1.74.0/BoostConfig.cmake (found suitable version "1.74.0", minimum required is "1.46.1") found components: filesystem system


# Check if boost was found
if(Boost_FOUND)
    message("boost found")
else()
    message(FATAL_ERROR "Cannot find Boost")
endif()

# boost found

# Add an executable
add_executable(third_party_include main.cpp)

# Link against the boost libraries
target_link_libraries(third_party_include
    PRIVATE
        Boost::filesystem # automatically adds Boost::boost and Boost::system dependencies
)

