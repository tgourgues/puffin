cmake_minimum_required(VERSION 3.0)

project(puffin_standard)

add_library(standard INTERFACE)
add_library(Puffin::standard ALIAS standard)

target_include_directories(standard
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  INTERFACE $<INSTALL_INTERFACE:include>
)

set(CMAKE_CXX_STANDARD 14)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS standard EXPORT PfnStandardTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT PfnStandardTargets
  FILE 
    PfnStandardTargets.cmake
  NAMESPACE
    Puffin::
  DESTINATION
    lib/cmake/pfnstd
)

export(TARGETS standard FILE PfnStandardTargets.cmake NAMESPACE Puffin::)