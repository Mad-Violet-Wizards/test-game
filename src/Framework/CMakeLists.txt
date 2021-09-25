project (onyx_engine_framework)

add_library(${PROJECT_NAME}
  src/DateTime.cpp
  src/Logs.cpp
  src/Prefixes.cpp
  src/Bitmask.cpp
)

# Set SFML, TGUI lib
if(WIN32)
	message("[Build System] Windows.")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-WINDOWS/lib/cmake/SFML")
	set(TGUI_DIR "${CMAKE_SOURCE_DIR}/../lib/TGUI-WINDOWS/lib/cmake/TGUI")
endif(WIN32)

if(UNIX)
  message("[Build system] Unix")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-LINUX/lib/cmake/SFML/")
endif(UNIX)

# Find packages for SFML, TGUI
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_library(onyx_engine::framework ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)