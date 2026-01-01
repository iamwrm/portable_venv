#!/bin/bash
set -e

# Detect architecture
ARCH=$(uname -m)

case "$ARCH" in
    x86_64)
        BINARY="pixi-unpack-x86_64-unknown-linux-musl"
        ;;
    aarch64)
        BINARY="pixi-unpack-aarch64-unknown-linux-musl"
        ;;
    *)
        echo "Unsupported architecture: $ARCH"
        exit 1
        ;;
esac

URL="https://github.com/Quantco/pixi-pack/releases/latest/download/$BINARY"
echo "Downloading pixi-unpack for $ARCH..."
curl -fsSL "$URL" -o pixi-unpack
chmod +x pixi-unpack
echo "Done: ./pixi-unpack"
