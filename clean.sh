#!/bin/bash
cd $(dirname "$0")

source scripts/flags.sh
rm -rf $GTEST_BUILD_DIR
rm -rf $ROOT_BUILD_DIR
rm -rf $RANGEV3_BUILD_DIR
