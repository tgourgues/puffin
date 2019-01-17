cmake_minimum_required(VERSION 3.0)

project(puffin)

option(BUILD_TESTS OFF)
option(BUILD_SAMPLES ON)

add_subdirectory(include/puffin/standard)
add_subdirectory(include/puffin/logging)
add_subdirectory(include/puffin/events)
add_subdirectory(include/puffin/uri)

if(BUILD_SAMPLES)
    add_subdirectory(samples)
endif()

if (BUILD_TESTS)
    enable_testing()
    include(cmake/externals/catch.cmake)
    add_subdirectory(tests)
endif()