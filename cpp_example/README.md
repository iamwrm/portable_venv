# Portable C++ with zstd Example

Demonstrates distributing a C++ application with native library dependencies using pixi-pack.

## What's Included

| Component | Version |
|-----------|---------|
| GCC | 14.3.0 |
| Clang | 21.1.7 |
| zstd | 1.5.7 |

## Build & Run Locally

```bash
# Test with both compilers
pixi run test

# Or run individually
pixi run run-gcc
pixi run run-clang
```

## Create Portable Distribution

```bash
pixi global install pixi-pack
pixi-pack -o env.tar
```

## Deploy to Target (no compiler/libraries needed!)

```bash
# Extract environment
./pixi-unpack env.tar -o /app

# Compile with GCC
env/bin/c++ -o myapp main.cpp -I env/include -L env/lib -lzstd

# Or compile with Clang
env/bin/clang++ -o myapp main.cpp -I env/include -L env/lib -lzstd

# Run (libraries are bundled)
LD_LIBRARY_PATH=env/lib ./myapp
```

## Archive Size

~200 MB (includes GCC, Clang, zstd, and all dependencies)

## Available Tasks

| Task | Description |
|------|-------------|
| `pixi run test` | Build and run with both GCC and Clang |
| `pixi run run-gcc` | Build and run with GCC only |
| `pixi run run-clang` | Build and run with Clang only |
| `pixi run build-gcc` | Build only (GCC) |
| `pixi run build-clang` | Build only (Clang) |
