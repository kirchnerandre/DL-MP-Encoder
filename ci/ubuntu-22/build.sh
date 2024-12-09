#!/bin/bash

pushd ./
mkdir -p build
cd       build
cmake -DPLATFORM=Linux ..
make
popd
