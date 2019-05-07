cmake_minimum_required(VERSION 3.0)

project(puffin_common)

add_library(common INTERFACE)
add_library(Puffin::common ALIAS common)

target_include_directories(common
  INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  INTERFACE $<INSTALL_INTERFACE:include>
)

target_compile_features(common 
  INTERFACE
    cxx_constexpr
    cxx_variadic_templates
    cxx_lambdas
    cxx_raw_string_literals
)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS standard EXPORT PuffinCommonTargets
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  INCLUDES DESTINATION include
)

install(EXPORT PuffinCommonTargets
  FILE 
  PuffinCommonTargets.cmake
  NAMESPACE
    Puffin::
  DESTINATION
    lib/cmake/puffin
)

export(TARGETS standard FILE PuffinCommonTargets.cmake NAMESPACE Puffin::)