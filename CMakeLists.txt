# CMake minimum version requirement
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(CommandAliasManager VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for headers
include_directories(${PROJECT_SOURCE_DIR}/CommandAliasManager/include)

# Locate libraries using vcpkg
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost REQUIRED)
find_package(JsonCpp REQUIRED)

# Set source and header files based on existing structure
file(GLOB SOURCES "CommandAliasManager/src/*.cpp")
file(GLOB HEADERS "CommandAliasManager/include/*.h")

# Add executable target for the project
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link with necessary libraries
target_link_libraries(${PROJECT_NAME} Qt5::Widgets ${Boost_LIBRARIES} ${JsonCpp_LIBRARIES})
