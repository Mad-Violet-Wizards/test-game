project (core) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

if (DEBUG)
  set(COMPILE_OPTIONS
    /FI${CMAKE_CURRENT_SOURCE_DIR}/engine_pch.hpp
    /DEBUG:FULL
    /ZI
    /Od
    /Ob0
    /std:c++20
    -D_CRT_SECURE_NO_WARNINGS
    -D__asm=__wrapped_asm
  )
endif()

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Animation/ Animation)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Components/ Components)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Debug/ Debug)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Events/ Events)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Filesystem/ Filesystem)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Input/ Input)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Level/ Level)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Objects/ Objects)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Scene/ Scene)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Utility/ Utility)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Window/ Window)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Projectiles/ Projectiles)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/Threads/ Threads)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${Animation} ${Components} ${Debug} ${Events} ${Filesystem} ${Input} ${Level} ${Objects} ${Scene} ${Utility} ${Window} ${Projectiles} ${Threads})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/Animation
  PUBLIC ${PROJECT_SOURCE_DIR}/Components
  PUBLIC ${PROJECT_SOURCE_DIR}/Debug
  PUBLIC ${PROJECT_SOURCE_DIR}/Events
  PUBLIC ${PROJECT_SOURCE_DIR}/Filesystem
  PUBLIC ${PROJECT_SOURCE_DIR}/Input
  PUBLIC ${PROJECT_SOURCE_DIR}/Level
  PUBLIC ${PROJECT_SOURCE_DIR}/Objects
  PUBLIC ${PROJECT_SOURCE_DIR}/Scene
  PUBLIC ${PROJECT_SOURCE_DIR}/Utility
  PUBLIC ${PROJECT_SOURCE_DIR}/Window
  PUBLIC ${PROJECT_SOURCE_DIR}/Containers
  PUBLIC ${PROJECT_SOURCE_DIR}/Projectiles
  PUBLIC ${PROJECT_SOURCE_DIR}/Threads
)

target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILE_OPTIONS})

target_link_libraries(${PROJECT_NAME} external)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/engine_pch.hpp)