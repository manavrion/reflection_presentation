# Download and unpack googletest at configure time
configure_file(cmake/nlohmann_json.cmake.in
               nlohmann_json-download/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download)

if(result)
  message(FATAL_ERROR "CMake step for nlohmann_json failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-download)

if(result)
  message(FATAL_ERROR "Build step for nlohmann_json failed: ${result}")
endif()

set(JSON_BuildTests OFF)

add_subdirectory(
  ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-src
  ${CMAKE_CURRENT_BINARY_DIR}/nlohmann_json-build EXCLUDE_FROM_ALL)
