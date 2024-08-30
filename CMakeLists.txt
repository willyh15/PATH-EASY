cmake_minimum_required(VERSION 3.15)
project(CommandAliasManager)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/willh/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable debug information and other options
set(CMAKE_BUILD_TYPE Debug)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS filesystem regex program_options)

# Find Nana GUI library
find_package(nana CONFIG REQUIRED)

# Add your executable
add_executable(CommandAliasManager main.cpp)  # Replace with your source files

# Link libraries to your executable
target_link_libraries(CommandAliasManager PRIVATE Boost::filesystem Boost::regex Boost::program_options nana::nana)

# Include directories
target_include_directories(CommandAliasManager PRIVATE ${Boost_INCLUDE_DIRS} ${NANA_INCLUDE_DIRS})
