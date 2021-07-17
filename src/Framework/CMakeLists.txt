project (onyx_engine_framework)

add_library(${PROJECT_NAME}
  Logs/Logs.cpp
  Time/DateTime.cpp
)

# Set SFML lib
set(SFML_DIR "../../lib/cmake/SFML/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_library(onyx_engine::framework ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)