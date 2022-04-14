project (onyx_engine_gui) # Specify the name of project

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/ CORE)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Scene WIDGETS)

# Specify the whole game as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${CORE} ${WIDGETS})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Include all needed libraries.
target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
  onyx_engine::game
)

add_library(onyx_engine::gui ALIAS ${PROJECT_NAME})

# Include all header files.
target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Widgets/
)