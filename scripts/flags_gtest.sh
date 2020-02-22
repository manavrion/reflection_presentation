#!/bin/bash

export GTEST_REPOSITORY_DIR=$ROOT_REPOSITORY_DIR/submodules/googletest
export GTEST_BUILD_DIR=$GTEST_REPOSITORY_DIR/build
export GTEST_INSTALL_DIR=$GTEST_REPOSITORY_DIR/build/install

# Cmake details

export GTEST_INCLUDE_DIR=$GTEST_INSTALL_DIR/include

if [ $BUILD_TYPE == Debug ]; then
    export GTEST_LIBRARY=$GTEST_INSTALL_DIR/lib/libgtestd.a
    export GTEST_MAIN_LIBRARY=$GTEST_INSTALL_DIR/lib/libgtest_maind.a
else
    export GTEST_LIBRARY=$GTEST_INSTALL_DIR/lib/libgtest.a
    export GTEST_MAIN_LIBRARY=$GTEST_INSTALL_DIR/lib/libgtest_main.a
fi
