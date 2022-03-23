project (onyx_engine_app)  # Specify the name of project

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJECT_NAME} main.cpp)

# Include all needed libraries.
target_link_libraries(${PROJECT_NAME} 
  onyx_engine::game
)
