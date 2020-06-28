# Tools
set(COMPILER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/.compiler/install)

set(CMAKE_C_COMPILER ${COMPILER_DIR}/bin/clang)
set(CMAKE_CXX_COMPILER ${COMPILER_DIR}/bin/clang++)

set(CMAKE_AR ${COMPILER_DIR}/bin/llvm-ar)
set(CMAKE_LINKER ${COMPILER_DIR}/bin/llvm-link)
set(CMAKE_NM ${COMPILER_DIR}/bin/llvm-nm)
set(CMAKE_OBJDUMP ${COMPILER_DIR}/bin/llvm-objdump)
set(CMAKE_RANLIB ${COMPILER_DIR}/bin/llvm-ranlib)

# Build
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++2a -freflection -I${COMPILER_DIR}/include")
