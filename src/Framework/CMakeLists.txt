project (onyx_engine_framework)

file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} ${SRC_FILES}
)

# Set SFML
if(WIN32)
	message("[Build System] Windows.")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-WINDOWS/lib/cmake/SFML")
endif(WIN32)

if(UNIX)
  message("[Build system] Unix")
	set(SFML_DIR "${CMAKE_SOURCE_DIR}/../lib/SFML-LINUX/lib/cmake/SFML/")
endif(UNIX)

# Find packages for SFML
find_package(SFML 2.5.1 COMPONENTS graphics audio REQUIRED)

add_library(onyx_engine::framework ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)
target_include_directories( ${PROJECT_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)