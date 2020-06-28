cmake_minimum_required(VERSION 3.8)
project(01_aggregate_reflection_bonus)

set(HEADER_FILES for_each.h magic_io.h)
set(SOURCE_FILES main.cc)

source_group("headers" FILES ${HEADER_FILES})
source_group("sources" FILES ${SOURCE_FILES})

add_executable(01_aggregate_reflection_bonus ${SOURCE_FILES} ${HEADER_FILES})
