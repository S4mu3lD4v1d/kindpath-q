#!/usr/bin/env bash
set -euo pipefail

BUILD_DIR=${BUILD_DIR:-build}
GENERATOR=${GENERATOR:-Ninja}
BUILD_TYPE=${BUILD_TYPE:-Debug}

cmake -S . -B "${BUILD_DIR}" -G "${GENERATOR}" -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
cmake --build "${BUILD_DIR}" --config "${BUILD_TYPE}"
