cmake_minimum_required(VERSION 3.15)

project(coreTest)

enable_testing()

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ SRC)

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} core sfml-window sfml-graphics sfml-system gtest)
