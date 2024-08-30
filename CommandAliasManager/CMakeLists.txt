cmake_minimum_required(VERSION 3.15)

# Set the project name
project(MyApp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add vcpkg integration
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
else()
    message(FATAL_ERROR "Please set the VCPKG_ROOT environment variable to the path of your vcpkg installation.")
endif()

# Add the source files
set(SOURCES
    src/MainApp.cpp
    src/AliasManager.cpp
    src/MainDlg.cpp
    src/PathManager.cpp
)

# Add the include directories
include_directories(include)

# Add executable
add_executable(MyApp ${SOURCES})

# Find and link the Nana library
find_package(nana CONFIG REQUIRED)
target_link_libraries(MyApp PRIVATE nana)

# Find and link the Boost library
find_package(Boost REQUIRED COMPONENTS filesystem)
target_link_libraries(MyApp PRIVATE Boost::filesystem)

# Find and link the JSON library (jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(MyApp PRIVATE jsoncpp_lib)

# Include the directories where the headers are located
target_include_directories(MyApp PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(MyApp PRIVATE ${NANA_INCLUDE_DIRS})
target_include_directories(MyApp PRIVATE ${JSONCPP_INCLUDE_DIRS})