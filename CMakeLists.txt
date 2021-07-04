# Set minimum required version for CMAKE
cmake_minimum_required(VERSION 3.2)

# Set name of project
project (onyx_engine)
set(CMAKE_CXX_STANDARD 20)

# Add all sources file to build
set(SOURCES 
    src/main.cpp
    src/Time/DateTime.cpp
    src/Logs/Logs.cpp
)

# Set SFML lib
set(SFML_DIR "lib/cmake/SFML/")

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

# Add executable file to use when builded
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)