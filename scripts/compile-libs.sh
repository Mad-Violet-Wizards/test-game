#!/bin/bash

echo "[Build system] Starting building TGUI library."
cd ../lib/TGUI-LINUX/
cmake .
make
echo "[Build system] Finished building TGUI library."
