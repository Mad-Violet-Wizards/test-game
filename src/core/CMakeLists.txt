project (core) # Specify the name of project

# Set the C++ "version"
set(CMAKE_CXX_STANDARD 20)

IF(MSVC)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
ENDIF()

# List the source files for all folders.
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Animation/ ANIMATION)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Components/ COMPONENTS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Debug/ DEBUG)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Events/ EVENTS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Filesystem/ FILESYSTEM)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Input/ INPUT)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Level/ LEVEL)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Objects/ OBJECTS)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Scene/ SCENE)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Utility/ UTILITY)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Window/ WINDOW)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src/Projectiles/ PROJECTILES)

# Specify the whole framework as a library and add source files. (cpp)
add_library(${PROJECT_NAME} ${ANIMATION} ${COMPONENTS} ${DEBUG} ${EVENTS} ${FILESYSTEM} ${INPUT} ${LEVEL} ${OBJECTS} ${SCENE} ${UTILITY} ${WINDOW} ${PROJECTILES})

# Include Conan.
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Include all header files.
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include/ANIMATION
  PUBLIC ${PROJECT_SOURCE_DIR}/include/COMPONENTS
  PUBLIC ${PROJECT_SOURCE_DIR}/include/DEBUG
  PUBLIC ${PROJECT_SOURCE_DIR}/include/EVENTS
  PUBLIC ${PROJECT_SOURCE_DIR}/include/FILESYSTEM
  PUBLIC ${PROJECT_SOURCE_DIR}/include/INPUT
  PUBLIC ${PROJECT_SOURCE_DIR}/include/LEVEL
  PUBLIC ${PROJECT_SOURCE_DIR}/include/OBJECTS
  PUBLIC ${PROJECT_SOURCE_DIR}/include/SCENE
  PUBLIC ${PROJECT_SOURCE_DIR}/include/UTILITY
  PUBLIC ${PROJECT_SOURCE_DIR}/include/WINDOW
  PUBLIC ${PROJECT_SOURCE_DIR}/include/CONTAINERS
  PUBLIC ${PROJECT_SOURCE_DIR}/include/PROJECTILES
)

target_link_libraries(${PROJECT_NAME} external)
target_link_options(${PROJECT_NAME} PUBLIC "/NODEFAULTLIB:libcmt.lib /NODEFAULTLIB:libcmtd.lib /NODEFAULTLIB:msvcrtd.lib")