#!/usr/bin/env bash

pushd build
# cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .
cmake -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" -GNinja ..
cmake --build .
popd
