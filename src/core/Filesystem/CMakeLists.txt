cmake_minimum_required(VERSION 3.15)

project(Filesystem VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(Filesystem ${SRC})
target_include_directories(Filesystem PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Filesystem PUBLIC external)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CORE_PRECOMPILED_HEADERS})