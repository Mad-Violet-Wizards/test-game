cmake_minimum_required(VERSION 3.15)

project (app) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

IF(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
ENDIF()

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} core gui game sfml-window sfml-graphics sfml-system ${ONYX_LIB_COMPRESSOR})
target_link_options(${PROJECT_NAME} PRIVATE "/NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib")