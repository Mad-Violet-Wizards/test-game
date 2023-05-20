cmake_minimum_required(VERSION 3.15)

project (app VERSION 0.1) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} core gui game sfml-window Filesystem sfml-graphics sfml-system)
