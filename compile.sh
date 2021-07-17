#!/bin/bash


echo "[Build system] Starting building onyx-engine project."
cd build
cmake ../src
make
echo "[Build system] Finished building onyx-engine project."
cd App
./onyx_engine_app