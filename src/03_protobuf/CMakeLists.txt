cmake_minimum_required(VERSION 3.8)
project(03_protobuf)

add_subdirectory(protos)

set(SOURCE_FILES main.cc)

source_group("sources" FILES ${SOURCE_FILES})

include_directories(${CMAKE_BINARY_DIR}/src/)

add_executable(03_protobuf ${SOURCE_FILES})
target_link_libraries(03_protobuf protobuf::libprotobuf protos)
