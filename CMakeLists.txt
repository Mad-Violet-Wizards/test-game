# Set minimum version of cmake
cmake_minimum_required (VERSION 3.15)

# Specify the project name
project(onyx_engine)

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(DEBUG) # Enable to use DEBUG mode.

set(ONYX_LIB_COMPRESSOR ${CMAKE_CURRENT_SOURCE_DIR}/tools/onyx_lib_compressor.lib)

IF (NOT DEFINED ${ONYX_LIB_COMPRESSOR})
  message("onyx_lib_compressor.lib not found! You should build tools.")
ENDIF()

IF(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
ENDIF()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/gui) 
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/game)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app)
