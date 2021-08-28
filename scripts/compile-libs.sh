#!/bin/bash

echo "[Build system] Starting building TGUI library."
cd ../lib/TGUI/
cmake .
make
echo "[Build system] Finished building TGUI library."