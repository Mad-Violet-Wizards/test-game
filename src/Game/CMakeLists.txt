project (onyx_engine_game) # Specify the name of project

# List the source files for all folders.
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB SCENE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Scene/*.cpp)
file(GLOB COMPONENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/*.cpp)

# Specify the whole game as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${SRC_FILES} ${SCENE_SRC_FILES} ${COMPONENT_SRC_FILES})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
 
# Include all needed libraries.
target_link_libraries(${PROJECT_NAME}
  ${CONAN_LIBS_SFML}
  onyx_engine::framework
  onyx_engine::gui
)

add_library(onyx_engine::game ALIAS ${PROJECT_NAME})

# Include all header files.
target_include_directories(${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Scene
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Components
)