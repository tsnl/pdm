#!/bin/bash

BUILD_TYPE="Debug"

# building the LLVM project:
# see: https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm
pushd dep/build-llvm
cmake ../llvm-project/llvm \
    -DLLVM_ENABLE_PROJECTS='clang' \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
cmake --build ../llvm-project/llvm
popd

# building source for the parser:
pushd src/pdm/parser
./bison-build.sh -Wnone
popd

# cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .
cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" .
cmake --build .

