project (game) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/GameplayComponents/ GAMEPLAY_COMPONENTS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ SRC)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${SRC} ${GAMEPLAY_COMPONENTS})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/GameplayComponents
)

target_link_libraries(${PROJECT_NAME} external core gui)
