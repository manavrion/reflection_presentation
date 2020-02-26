cmake_minimum_required(VERSION 3.8)
project(template_repository)

# The code uses the root folder to #include
include_directories("src/")

# Google test
enable_testing()
find_package(GTest REQUIRED)

# magic_get
include_directories(${MAGIC_GET_INSTALL_DIR})

# Json
include_directories(${NJSON_INCLUDE_DIR})

add_subdirectory(src)
