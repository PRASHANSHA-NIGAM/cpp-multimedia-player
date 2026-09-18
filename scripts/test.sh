#!/bin/bash

# ==========================================
# C++ Multimedia Player - Test Script
# ==========================================

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"


echo "=========================================="
echo " C++ Multimedia Player - Tests"
echo "=========================================="


echo ""
echo "Building test target..."

cmake --build "$BUILD_DIR"


echo ""
echo "Running tests..."

ctest \
    --test-dir "$BUILD_DIR" \
    --output-on-failure


echo ""
echo "=========================================="
echo " All tests passed!"
echo "=========================================="
