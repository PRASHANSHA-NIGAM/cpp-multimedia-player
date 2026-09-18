#!/bin/bash

# ==========================================
# C++ Multimedia Player - Deployment Script
# ==========================================

set -e

PROJECT_ROOT="$(cd "$(dirname "$0")/.." && pwd)"

BUILD_DIR="$PROJECT_ROOT/build"
INSTALL_DIR="$PROJECT_ROOT/release"
PACKAGE_DIR="$PROJECT_ROOT/packages"

PACKAGE_NAME="MediaPlayer-Linux.tar.gz"


echo "=========================================="
echo " C++ Multimedia Player - Deployment"
echo "=========================================="


# ==========================================
# STEP 1: Clean old directories
# ==========================================

echo ""
echo "Cleaning old deployment files..."

rm -rf "$INSTALL_DIR"
rm -rf "$PACKAGE_DIR"


# ==========================================
# STEP 2: Configure Release build
# ==========================================

echo ""
echo "Configuring Release build..."

cmake -S "$PROJECT_ROOT" \
      -B "$BUILD_DIR" \
      -DCMAKE_BUILD_TYPE=Release


# ==========================================
# STEP 3: Build
# ==========================================

echo ""
echo "Building application..."

cmake --build "$BUILD_DIR"


# ==========================================
# STEP 4: Install
# ==========================================

echo ""
echo "Installing application..."

cmake --install "$BUILD_DIR" \
      --prefix "$INSTALL_DIR"


# ==========================================
# STEP 5: Create package directory
# ==========================================

echo ""
echo "Creating package..."

mkdir -p "$PACKAGE_DIR"


# ==========================================
# STEP 6: Create tar.gz
# ==========================================

tar -czf \
    "$PACKAGE_DIR/$PACKAGE_NAME" \
    -C "$INSTALL_DIR" .


# ==========================================
# DONE
# ==========================================

echo ""
echo "=========================================="
echo " Deployment completed successfully!"
echo "=========================================="

echo ""
echo "Package:"
echo "$PACKAGE_DIR/$PACKAGE_NAME"
