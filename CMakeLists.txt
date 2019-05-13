cmake_minimum_required(VERSION 3.11)

project(puffin_meta)

file(COPY ${CMAKE_SOURCE_DIR}/cmake/PuffinHelpers.cmake DESTINATION ${CMAKE_BINARY_DIR}/cmake)

add_subdirectory(common)
add_subdirectory(events)