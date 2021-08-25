project (onyx_engine_app)

add_executable(${PROJECT_NAME} main.cpp)

# Set SFML lib
set(SFML_DIR "../../lib/SFML/lib/cmake/SFML/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
  onyx_engine::game
)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
