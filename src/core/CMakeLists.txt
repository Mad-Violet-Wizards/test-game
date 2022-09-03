project (core) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ SRC)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${SRC})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} external game)