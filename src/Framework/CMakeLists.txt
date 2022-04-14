project (onyx_engine_framework) # Specify the name of project

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ CORE)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Input INPUT)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Window WINDOW)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Scene SCENE)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${CORE} ${INPUT} ${WINDOW} ${SCENE})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_library(onyx_engine::framework ALIAS ${PROJECT_NAME})

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Input/
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Window/
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Scene/
)