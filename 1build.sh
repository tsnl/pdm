#!/bin/bash

pushd src/pdm/parser
./bison-build.sh -Wnone
popd

cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .
cmake --build .

