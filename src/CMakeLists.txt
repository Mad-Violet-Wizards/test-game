#
# Main CMake file,
# Author: Mateusz (@hoopdead)
#

# Set minimum version of cmake
cmake_minimum_required (VERSION 3.2)

# Specify the project name
project(onyx_engine)

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Framework) # Add subdirectory - Framework, also look at CMakeLists at Framework dir.
add_subdirectory(Game) # Add subdirectory - Game, also look at CMakeLists at Game dir.
add_subdirectory(App) # Add subdirectory - App, also look at CmakeLists at App dir.
