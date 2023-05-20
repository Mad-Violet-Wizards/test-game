cmake_minimum_required(VERSION 3.15)

project(pak-compiler VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_executable(${PROJECT_NAME} main.cpp)
