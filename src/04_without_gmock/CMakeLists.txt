cmake_minimum_required(VERSION 3.8)
project(04_without_gmock)

set(HEADER_FILES browser.h)
set(SOURCE_FILES test.cc)

source_group("headers" FILES ${HEADER_FILES})
source_group("sources" FILES ${SOURCE_FILES})

add_executable(04_without_gmock ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(04_without_gmock gtest gtest_main pthread)
add_test(04_without_gmock 04_without_gmock)
