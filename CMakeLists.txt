# Set minimum required version for CMAKE
cmake_minimum_required(VERSION 3.2)

# Set name of project
project (onyx_engine)

# Add all sources file to build
set(SOURCES 
    src/main.cpp
    src/Time/DateTime.cpp
)

# Set SFML lib
set(SFML_DIR "lib/SFML/cmake/SFML/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

# Add executable file to use when builded
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)