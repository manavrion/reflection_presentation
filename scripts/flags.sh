#!/bin/bash

# Used for CI
if [ ! -v CMAKE_BIN ]; then
    export CMAKE_BIN=cmake
fi

source scripts/flags_root.sh

# Toolchain file
export CMAKE_TOOLCHAIN_FILE=$ROOT_REPOSITORY_DIR/toolchain.cmake

# Used at toolchain.cmake
export COMPILER_DIR=$ROOT_REPOSITORY_DIR/compiler/install

# Build type needed by toolchain.cmake and gtest
if [ ! -v BUILD_TYPE ]; then
    export BUILD_TYPE=Debug
fi

source scripts/flags_gtest.sh

source scripts/flags_rangev3.sh
