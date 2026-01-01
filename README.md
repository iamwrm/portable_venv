# Portable Python Environment with Pixi

Create a fully portable Python environment that can be deployed to a bare Linux system (no Python required).

## Overview

This project demonstrates how to use [Pixi](https://pixi.sh) and [pixi-pack](https://github.com/Quantco/pixi-pack) to create self-contained Python environments that can be copied to any compatible Linux machine.

## Prerequisites

Install Pixi on your development machine:

```bash
curl -fsSL https://pixi.sh/install.sh | bash
```

## Quick Start

### 1. Create your project

```bash
pixi init
pixi add python=3.12 requests httpx  # add your dependencies
```

### 2. Create portable archive

```bash
# Install pixi-pack
pixi global install pixi-pack

# Create the archive
pixi-pack -o env.tar
```

### 3. Deploy to target machine

Copy these files to your target:
- `env.tar` - The portable environment archive
- `pixi-unpack` - Static binary to extract the environment ([download](https://github.com/Quantco/pixi-pack/releases))
- Your application files

```bash
# On target machine (no Python needed!)
./pixi-unpack env.tar -o /app
./env/bin/python your_app.py
```

## Project Structure

```
.
├── pixi.toml          # Pixi project configuration
├── pixi.lock          # Locked dependencies
├── test_venv.py       # Test script
├── env.tar            # Portable archive (generated)
└── pixi-unpack        # Extractor binary (downloaded)
```

## How It Works

1. **Pixi** manages Python and dependencies using conda-forge packages
2. **pixi-pack** downloads all packages and creates a compressed archive
3. **pixi-unpack** extracts and links packages into a working environment
4. The result is a self-contained `env/` directory with Python and all dependencies

## Comparison with uv

| Feature | uv + rsync | pixi-pack |
|---------|------------|-----------|
| Requires `rsync -L` flag | Yes (to dereference symlinks) | No |
| Extra tool on target | No | Yes (`pixi-unpack`, ~5MB) |
| Archive size | ~100MB+ | ~45MB (compressed) |
| Handles C extensions | Via wheels | Via conda (better) |
| Designed for deployment | Not really | Yes |

## Requirements

- **Architecture must match**: x86_64 → x86_64, arm64 → arm64
- **Linux glibc compatibility**: Target should have compatible glibc version

## Testing Locally

```bash
# Create and test the portable environment
pixi run python test_venv.py

# Test in a bare Debian container
docker run --rm -v $(pwd):/app -w /app debian:13 bash -c "
  ./pixi-unpack env.tar -o /app
  ./env/bin/python test_venv.py
"
```

## License

MIT
