#!/usr/bin/env bash

BUILD_TYPE="Debug"
# NUM_PARALLEL_JOBS=`nproc`
# echo "[Pdm] Building with ${NUM_PARALLEL_JOBS} parallel jobs."
echo "[Pdm] building with Ninja"

# building the LLVM project:
# - build directory: /build/llvm
# - install directory: /build/llvm/install
# see: https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm
pushd ./build/llvm/ || exit 1
cmake ../../dep/llvm-project/llvm \
    -DLLVM_ENABLE_PROJECTS='clang;compiler-rt' \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DLLVM_BUILD_LLVM_DYLIB="OFF" \
    -GNinja
cmake --build .
cmake -DCMAKE_INSTALL_PREFIX="./install" -P cmake_install.cmake
popd || exit 1

# building source for the parser:
bash top-bison-build.sh

# rebuilding sources now that everything is configured:
bash rebuild.sh
