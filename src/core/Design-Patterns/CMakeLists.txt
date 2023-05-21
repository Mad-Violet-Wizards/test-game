cmake_minimum_required(VERSION 3.15)

project(Design-Patterns VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE .)

if(TESTS)
  add_subdirectory(Tests)
endif()