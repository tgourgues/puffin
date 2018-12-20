cmake_minimum_required(VERSION 3.0)

set(TEST_SOURCES 
  tests_event_bus               
)

add_executable(tests "tests_main" ${TEST_SOURCES})
target_link_libraries(tests Puffin::events Catch)

add_test(NAME Puffin COMMAND tests)