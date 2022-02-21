project (onyx_engine_framework) # Specify the name of project

# List the source files for all folders.
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${SRC_FILES})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(onyx_engine::framework ALIAS ${PROJECT_NAME})

# Include all needed libraries.
target_link_libraries(${PROJECT_NAME} 
  ${CONAN_LIBS_SFML}
)

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)