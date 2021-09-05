#
# Main CMake file,
# Author: Mateusz (@hoopdead)
#

# Set minimum version of cmake
cmake_minimum_required (VERSION 3.2)

# Specify the project name
project(onyx_engine)

# We need to make sure, that SFML dlls are copied into build/App directory, otherwise, there will be compilation error.
if(WIN32)
	file (GLOB SFML_DLL "../lib/SFML-WINDOWS/bin/*.dll")
	file (COPY ${SFML_DLL} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/App/")
endif(WIN32)
# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Framework) # Add subdirectory - Framework, also look at CMakeLists at Framework dir.
add_subdirectory(Game) # Add subdirectory - Game, also look at CMakeLists at Game dir.
add_subdirectory(App) # Add subdirectory - App, also look at CmakeLists at App dir.
