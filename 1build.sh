#!/bin/bash

BUILD_TYPE="Debug"
# NUM_PARALLEL_JOBS=`nproc`
# echo "[Pdm] Building with ${NUM_PARALLEL_JOBS} parallel jobs."
echo "[Pdm] building with Ninja"

# # building the LLVM project:
# # see: https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm
# pushd dep/build-llvm-project
# cmake ../llvm-project/llvm \
#     -DLLVM_ENABLE_PROJECTS='all' \
#     -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
# cmake --build --parallel 4 ../llvm-project/llvm
# popd

# building source for the parser:
pushd src/pdm/parser
./bison-build.sh -Wnone
popd

pushd build
# cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .
cmake \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DLLVM_ENABLE_PROJECTS='clang;compiler-rt' \
    -GNinja \
    ..
cmake --build .
popd
