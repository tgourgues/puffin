cmake_minimum_required(VERSION 3.0)

add_executable(sample_logging "sample_logging.cpp")
target_link_libraries(sample_logging Puffin::logging)

add_executable(sample_event_bus "sample_event_bus.cpp")
target_link_libraries(sample_event_bus Puffin::events)
