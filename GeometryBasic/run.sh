#!/bin/zsh

EXAMPLE=${1:-01_union}

cmake -S . -B build \
    -DEXAMPLE=${EXAMPLE}

cmake --build build &&
./build/GeometryBasic