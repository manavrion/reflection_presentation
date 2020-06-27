# Download and unpack googletest at configure time
configure_file(cmake/protobuf.cmake.in
               protobuf-download/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protobuf-download)

if(result)
  message(FATAL_ERROR "CMake step for protobuf failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protobuf-download)

if(result)
  message(FATAL_ERROR "Build step for protobuf failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" ${CMAKE_CURRENT_BINARY_DIR}/protobuf-src/cmake
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protobuf-build)

if(result)
  message(FATAL_ERROR "CMake step 2 for protobuf failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build . -j 8
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protobuf-build)

if(result)
  message(FATAL_ERROR "Real build step for protobuf failed: ${result}")
endif()

# Make protobuf-install folder!
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protobuf-install)

execute_process(
  COMMAND ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/protobuf-install -P ${CMAKE_CURRENT_BINARY_DIR}/protobuf-build/cmake_install.cmake
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/protobuf-install)

if(result)
  message(FATAL_ERROR "Install step for protobuf failed: ${result}")
endif()

## add_subdirectory(
##   ${CMAKE_CURRENT_BINARY_DIR}/protobuf-src/cmake
##   ${CMAKE_CURRENT_BINARY_DIR}/protobuf-build EXCLUDE_FROM_ALL)
##  

find_package(Protobuf REQUIRED
  HINTS ${CMAKE_CURRENT_BINARY_DIR}/protobuf-install)
