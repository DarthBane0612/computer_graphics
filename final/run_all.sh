#!/usr/bin/env bash

# If project not ready, generate cmake file.
if [[ ! -d build ]]; then
    mkdir -p build
    cd build
    cmake ..
    cd ..
else
    rm -r build
    mkdir -p build
    cd build
    cmake ..
    cd ..
fi

# Build project.
cd build
make -j
cd ..

# Run all testcases. 
# You can comment some lines to disable the run of specific examples.
mkdir -p output
bin/final testcases/scene01_basic.txt output/scene01.bmp
bin/final testcases/scene02_cube.txt output/scene02.bmp
bin/final testcases/scene05_bunny_200.txt output/scene05.bmp
bin/final testcases/scene06_bunny_1k.txt output/scene06.bmp
