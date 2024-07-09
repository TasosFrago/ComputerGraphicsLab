#!/bin/sh

cd libigl
mkdir build
cd build
cmake ..
cmake -DLIBIGL_WITH_OPENGL=ON -DLIBIGL_WITH_VIEWER=ON ..

num_threads=$(grep -c ^processor /proc/cpuinfo)
make -j$num_threads
