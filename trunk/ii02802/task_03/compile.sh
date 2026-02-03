#!/usr/bin/env bash

set -euo pipefail

echo ""
echo "=== Building project (macOS / Linux) ==="
echo ""

mkdir -p build
cd build

echo "[1/4] Configuring CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release

echo ""
echo "[2/4] Building main program..."
cmake --build . --config Release --target task_3_ii02802 -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "[3/4] Building tests..."
cmake --build . --config Release --target testlab3_runner_ii02802 -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "[4/4] Running tests..."
if [[ -f ./testlab3_runner_ii02802 ]]; then
    echo "Running tests..."
    ./testlab3_runner_ii02802
else
    echo "Test executable not found: ./testlab3_runner_ii02802"
fi

echo ""
echo "Running main program..."
if [[ -f ./task_3_ii02802 ]]; then
    echo "Running main..."
    ./task_3_ii02802
    echo ""
    echo "Results saved to: simulation_results.csv"
else
    echo "Main executable not found: ./task_3_ii02802"
fi

cd ..
echo ""
echo "Done."
read -p "Press Enter to continue..."