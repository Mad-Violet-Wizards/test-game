cmake_minimum_required(VERSION 3.15)

project(Filesystem_Aseprite VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_library(${PROJECT_NAME} INTERFACE ${SRC})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

if (TESTS)
  add_subdirectory(Tests)
endif()