cmake_minimum_required(VERSION 3.0)

project(puffin_logging)

add_library(logging INTERFACE)
add_library(Puffin::logging ALIAS logging)

target_include_directories(logging
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
  INTERFACE $<INSTALL_INTERFACE:include>
)

target_compile_features(logging
  INTERFACE
    cxx_std_14
)

target_link_libraries(logging INTERFACE Puffin::standard)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS logging EXPORT PfnLoggingTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT PfnLoggingTargets
  FILE 
    PfnLoggingTargets.cmake
  NAMESPACE
    Puffin::
  DESTINATION
    lib/cmake/pfn
)

export(TARGETS logging FILE PfnLoggingTargets.cmake NAMESPACE Puffin::)