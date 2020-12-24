#!/bin/bash

pushd src/pdm/parser
./bison-build.sh -Wnone
popd

cmake --build .
