cmake_minimum_required(VERSION 3.8)
project(02_json_reflection)

set(HEADER_FILES for_each.h)
set(SOURCE_FILES main.cc)

source_group("headers" FILES ${HEADER_FILES})
source_group("sources" FILES ${SOURCE_FILES})

add_executable(02_json_reflection ${SOURCE_FILES} ${HEADER_FILES})
