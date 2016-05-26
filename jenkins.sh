#!/bin/sh
cd build
cmake ..
echo $1
if [ "$1" == true ]
then
    echo "Cleaning workspace..."
    make clean
fi
echo "Building and tests executing..."
make -j && make runTests
cd ..
