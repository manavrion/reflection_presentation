#!/bin/bash
cd $(dirname "$0")

rm -rf compiler
mkdir compiler
cd compiler
wget -nv https://github.com/manavrion/clang_hub/releases/download/v1.1/clang_of_lock3_compiler_explorer.tar.gz
tar -xf clang_of_lock3_compiler_explorer.tar.gz
rm clang_of_lock3_compiler_explorer.tar.gz
