#!/bin/bash

BUILD_DIR="./build"

# Check if directory exists
if [ -d "$BUILD_DIR" ]; then
    echo "[Build system] Starting building onyx-engine project."
    echo "[Build system] Found build directory."
    rm -rf build
    mkdir build
    cd build
    cmake ..
    make
    echo "[Build system] Finished building onyx-engine project."
else
    echo "[Build system] Starting building onyx-engine project."
    echo "[Build system] Did not found build directory."
    mkdir build
    cd build
    cmake ..
    make
    echo "[Build system] Finished building onyx-engine project."
fi