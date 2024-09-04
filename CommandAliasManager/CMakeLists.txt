cmake_minimum_required(VERSION 3.15)

# Project Name
project(CommandAliasManager)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Vcpkg integration
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Find Qt6 packages
set(QT_VERSION 6)  # Update from 5 to 6
find_package(Qt${QT_VERSION} COMPONENTS Core Gui Widgets REQUIRED)

# Include directories for headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS filesystem)

# Find JSON for Modern C++
find_package(jsoncpp CONFIG REQUIRED)

# Source files
set(SOURCES
    main.cpp
    src/AliasManager.cpp
    src/MainDlg.cpp
    src/ManageCommandsDialog.cpp
    src/PathManager.cpp
)

# Add executable
add_executable(CommandAliasManager ${SOURCES})

# Link Qt libraries
target_link_libraries(CommandAliasManager PRIVATE Qt${QT_VERSION}::Core Qt${QT_VERSION}::Gui Qt${QT_VERSION}::Widgets)

# Link Boost libraries
target_link_libraries(CommandAliasManager PRIVATE Boost::filesystem)

# Link JSON library
target_link_libraries(CommandAliasManager PRIVATE jsoncpp_lib)

# Include directories for libraries
target_include_directories(CommandAliasManager PRIVATE ${Boost_INCLUDE_DIRS} ${JSONCPP_INCLUDE_DIRS})
