cmake_minimum_required(VERSION 3.8)
project(01_aggregate_bin)

set(HEADER_FILES for_each.h magic_io.h)
set(SOURCE_FILES main.cc)

source_group("headers" FILES ${HEADER_FILES})
source_group("sources" FILES ${SOURCE_FILES})

add_executable(01_aggregate_bin ${SOURCE_FILES} ${HEADER_FILES})
