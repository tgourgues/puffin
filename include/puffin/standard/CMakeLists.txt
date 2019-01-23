cmake_minimum_required(VERSION 3.0)

project(puffin_standard)

add_library(standard INTERFACE)
add_library(Puffin::standard ALIAS standard)

target_include_directories(standard
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../..>
  INTERFACE $<INSTALL_INTERFACE:include>
)

target_compile_features(standard 
  INTERFACE
    cxx_constexpr
    cxx_variadic_templates
    cxx_lambdas
    cxx_raw_string_literals
)

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
    lib/cmake/pfn
)

export(TARGETS standard FILE PfnStandardTargets.cmake NAMESPACE Puffin::)