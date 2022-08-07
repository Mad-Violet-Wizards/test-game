project (external) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} INTERFACE)

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  INTERFACE include/
)