cmake_minimum_required(VERSION 3.8)
project(02_json)

set(SOURCE_FILES main.cc)

source_group("sources" FILES ${SOURCE_FILES})

add_executable(02_json ${SOURCE_FILES})
