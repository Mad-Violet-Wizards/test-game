# Set minimum version of cmake
cmake_minimum_required (VERSION 3.15)

# Specify the project name
project(onyx_engine)

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)
set(CORE_PRECOMPILED_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/core/engine_pch.hpp)

# Use this options exclusively.
option(DEBUG "Enable debug mode" ON)
option(RELEASE "Enable release mode" OFF)
option(TESTS "Enable tests" ON)

if (DEBUG)
  add_compile_definitions(DEBUG) # Enable to use DEBUG mode.
endif()

if (TESTS)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/cb455a71fb23303e37ce8ee5b1cde6a2c18f66a5.zip
  )

  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gui) 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/game)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/pak-compiler)
