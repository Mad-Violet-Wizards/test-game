project (onyx_engine_game)

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

# Set SFML lib
set(SFML_DIR "../../lib/cmake/SFML/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
)

add_library(onyx_engine::game ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Scene
  PUBLIC ${PROJECT_SOURCE_DIR}/include/Components
)