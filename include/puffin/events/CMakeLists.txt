cmake_minimum_required(VERSION 3.0)

project(puffin_events)

add_library(events INTERFACE)
add_library(Puffin::events ALIAS events)

target_include_directories(events
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
  INTERFACE $<INSTALL_INTERFACE:include>
)

target_link_libraries(events INTERFACE Puffin::standard)

set(CMAKE_CXX_STANDARD 14)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS standard EXPORT PfnEventsTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT PfnEventsTargets
  FILE 
    PfnEventsTargets.cmake
  NAMESPACE
    Puffin::
  DESTINATION
    lib/cmake/pfn
)

export(TARGETS events FILE PfnEventsTargets.cmake NAMESPACE Puffin::)