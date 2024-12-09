#!/bin/bash

pushd ./
rm -fR ./Data/Output 2> /dev/null
mkdir ./Data/Output
cd build
ctest --output-on-failure ..
popd
