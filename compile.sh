#!/bin/bash
# Test commit

echo "[Build system] Starting building onyx-engine project."
cd build
cmake ..
make
echo "[Build system] Finished building onyx-engine project."
./onyx_engine
