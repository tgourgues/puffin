cmake_minimum_required(VERSION 3.0)

project(puffin_webkit)

add_library(webkit INTERFACE)
add_library(Puffin::webkit ALIAS webkit)

target_include_directories(webkit
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
  INTERFACE $<INSTALL_INTERFACE:include>
)

target_compile_features(webkit
  INTERFACE
    cxx_std_11
)

target_link_libraries(webkit INTERFACE Puffin::standard)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS webkit EXPORT PfnWebkitTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT PfnWebkitTargets
  FILE 
    PfnWebkitTargets.cmake
  NAMESPACE
    Puffin::
  DESTINATION
    lib/cmake/pfn
)

export(TARGETS webkit FILE PfnWebkitTargets.cmake NAMESPACE Puffin::)