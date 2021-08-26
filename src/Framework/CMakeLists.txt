project (onyx_engine_framework)

add_library(${PROJECT_NAME}
  src/DateTime.cpp
  src/Logs.cpp
  src/Prefixes.cpp
  src/Bitmask.cpp
)

# Set SFML lib
set(SFML_DIR "../../lib/SFML/lib/cmake/SFML/")
set(TGUI_DIR "../../lib/TGUI/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)
find_package(TGUI REQUIRED)

add_library(onyx_engine::framework ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} tgui sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)