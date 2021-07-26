project (onyx_engine_game)

add_library(${PROJECT_NAME}
  src/Window.cpp
  src/Game.cpp
)

# Set SFML lib
set(SFML_DIR "../../lib/cmake/SFML/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_library(onyx_engine::game ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)