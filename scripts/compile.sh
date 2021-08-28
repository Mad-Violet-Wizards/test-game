#!/bin/bash

echo "[Build system] Starting building test-game project."
cd ../build
cmake ../src
make
echo "[Build system] Finished building test-game project."
cd App
./onyx_engine_app