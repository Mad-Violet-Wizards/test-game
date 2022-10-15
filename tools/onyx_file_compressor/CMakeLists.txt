cmake_minimum_required(VERSION 3.15)

project(onyx_lib_compressor)

set (CMAKE_CXX_STANDARD 20)

if (WIN32)
  message("WIN")
  add_compile_definitions(WINDOWS)
endif()

if (APPLE)
  add_compile_definitions(APPLE)
endif()

if (UNIX AND NOT APPLE)
  add_compile_definitions(LINUX)
endif()

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ SRC)

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(onyx_lib_compressor SHARED ${SRC})

target_include_directories(onyx_lib_compressor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} zlib)
