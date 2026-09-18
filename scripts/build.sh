#!/bin/bash

# ==========================================
# C++ Multimedia Player - Build Script
# ==========================================

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"


echo "=========================================="
echo " C++ Multimedia Player - Build"
echo "=========================================="

echo ""
echo "Project root:"
echo "$PROJECT_ROOT"

echo ""
echo "Cleaning old build directory..."

rm -rf "$BUILD_DIR"

echo ""
echo "Configuring CMake..."

cmake -S "$PROJECT_ROOT" \
      -B "$BUILD_DIR" \
      -DCMAKE_BUILD_TYPE=Release

echo ""
echo "Building project..."

cmake --build "$BUILD_DIR"

echo ""
echo "=========================================="
echo " Build completed successfully!"
echo "=========================================="

echo ""
echo "Executable:"
echo "$BUILD_DIR/MediaPlayer"
