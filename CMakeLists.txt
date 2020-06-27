cmake_minimum_required(VERSION 3.8)

include(toolchain.cmake)

project(reflection_presentation)

# Export dependencies
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Export compilation data-base
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(gtest)
include(magic_get)
include(nlohmann_json)
include(protobuf)
include(rangev3)

enable_testing()

include_directories("src/")

add_subdirectory(src)
