project (onyx_engine_app)

add_executable(${PROJECT_NAME} main.cpp)

# Set SFML, TGUI lib
set(SFML_DIR "../../lib/SFML/lib/cmake/SFML/")
set(TGUI_DIR "../../lib/TGUI/")

# Find packages for SFML, TGUI
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)
find_package(TGUI REQUIRED)

target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
  onyx_engine::game
)

target_link_libraries(${PROJECT_NAME} tgui sfml-graphics sfml-audio)
