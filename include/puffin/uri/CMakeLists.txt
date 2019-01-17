cmake_minimum_required(VERSION 3.0)

project(puffin_uri)

add_library(uri INTERFACE)
add_library(Puffin::uri ALIAS uri)

target_include_directories(uri
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
  INTERFACE $<INSTALL_INTERFACE:include>
)

target_compile_features(uri
  INTERFACE
    cxx_std_11
)

target_link_libraries(uri INTERFACE Puffin::standard)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS uri EXPORT PfnUriTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT PfnUriTargets
  FILE 
    PfnUriTargets.cmake
  NAMESPACE
    Puffin::
  DESTINATION
    lib/cmake/pfn
)

export(TARGETS uri FILE PfnUriTargets.cmake NAMESPACE Puffin::)