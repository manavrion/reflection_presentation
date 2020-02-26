cmake_minimum_required(VERSION 3.8)
project(protos)

set(PROTO_FILES user.proto)

source_group("protos" FILES ${PROTO_FILES})

add_library(protos ${PROTO_FILES})

target_link_libraries(protos protobuf::libprotobuf)
protobuf_generate(TARGET protos)
