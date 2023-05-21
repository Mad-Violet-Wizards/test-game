aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)

add_executable(${PROJECT_NAME}_Tests ${SRC})

target_link_libraries(${PROJECT_NAME}_Tests 
  PRIVATE 
  ${PROJECT_NAME}
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_Tests)