#!/bin/sh
cd build
cmake .
echo $1
if [ "$1" == true ]
then
    echo "Cleaning workspace..."
    make clean
fi
echo "Building..."
make -j
echo "Running tests..."
make runTests
cd ..
