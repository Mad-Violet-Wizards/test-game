project (onyx_engine_app)

add_executable(${PROJECT_NAME} main.cpp)

# Set SFML, TGUI lib
if(WIN32)
	message("[Build System] Windows.")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-WINDOWS/lib/cmake/SFML")
	set(TGUI_DIR "${CMAKE_SOURCE_DIR}/../lib/TGUI-WINDOWS/lib/cmake/TGUI")
endif(WIN32)

if(UNIX)
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-LINUX/lib/cmake/SFML/")
	set(TGUI_DIR "${CMAKE_SOURCE_DIR}/../lib/TGUI-LINUX/")
endif(UNIX)

# Find packages for SFML, TGUI
find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)
find_package(TGUI REQUIRED)

target_link_libraries(${PROJECT_NAME}
  onyx_engine::framework
  onyx_engine::game
)

target_link_libraries(${PROJECT_NAME} tgui sfml-graphics sfml-audio)
