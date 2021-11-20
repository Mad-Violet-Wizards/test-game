project (onyx_engine_game) # Specify the name of project

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB SCENE_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Scene/*.cpp)
file(GLOB COMPONENT_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/Components/*.cpp)

# Specify the whole game as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${SRC_FILES} ${SCENE_SRC_FILES} ${COMPONENT_SRC_FILES}
 )

# Set SFML
if(WIN32)
	message("[Build System] Windows.")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-WINDOWS/lib/cmake/SFML")
endif(WIN32)

if(UNIX)
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-LINUX/lib/cmake/SFML/")
endif(UNIX)

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
  onyx_engine::gui
)

add_library(onyx_engine::game ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Scene
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Components
)