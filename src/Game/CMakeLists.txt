project (onyx_engine_game) # Specify the name of project


# Specify the whole game as a library and add source files. (cpp)
add_library(${PROJECT_NAME}
  src/Window.cpp
  src/Game.cpp
  src/Input.cpp
  src/Object.cpp
  src/Scene/SceneStateMachine.cpp
  src/Scene/SceneGame.cpp
  src/Components/C_Sprite.cpp
  src/Components/C_Transform.cpp
  src/Components/C_KeyboardMovement.cpp
)

# Set SFML, TGUI lib
if(WIN32)
	message("[Build System] Windows.")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}../lib/SFML-WINDOWS/lib/cmake/SFML")
	set(TGUI_DIR "${CMAKE_SOURCE_DIR}../lib/TGUI-WINDOWS/lib/cmake/TGUI")
endif(WIN32)

if(UNIX)
	set(SFML_DIR "${CMAKE_SOURCE_DIR}../../lib/SFML/lib/cmake/SFML/")
	set(TGUI_DIR "${CMAKE_SOURCE_DIR}../../lib/TGUI/")
endif(UNIX)

# Find packages for SFML, TGUI
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(TGUI REQUIRED)

target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
)

add_library(onyx_engine::game ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} tgui sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Scene
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Components
)