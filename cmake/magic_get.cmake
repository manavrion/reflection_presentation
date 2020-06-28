# Download and unpack magic_get at configure time
configure_file(cmake/magic_get.cmake.in magic_get-download/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/magic_get-download)

if(result)
  message(FATAL_ERROR "CMake step for magic_get failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/magic_get-download)

if(result)
  message(FATAL_ERROR "Build step for magic_get failed: ${result}")
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR}/magic_get-src/include)
