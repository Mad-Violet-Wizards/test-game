# Set minimum version of cmake
cmake_minimum_required (VERSION 3.15)

# Specify the project name
project(onyx_engine)

set(CORE_PRECOMPILED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/core/engine_pch.hpp)

# Use this options exclusively.
option(DEBUG "Enable debug mode" ON)
option(RELEASE "Enable release mode" OFF)

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

if (DEBUG)
  add_compile_definitions(DEBUG) # Enable to use DEBUG mode.
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/core/Filesystem)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gui) 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/game)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/pak-compiler)
