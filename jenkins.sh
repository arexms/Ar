#!/bin/sh
cd build
cmake .
make -j
make runTests
cd ..
