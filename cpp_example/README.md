# Portable C++ with zstd Example

Demonstrates distributing a C++ application with native library dependencies using pixi-pack.

## What's included

- C++ compiler (GCC)
- zstd library (headers + shared library)
- All required runtime dependencies

## Build & Run Locally

```bash
pixi run run
```

## Create Portable Distribution

```bash
pixi-pack -o env.tar
```

## Deploy to Target (no compiler/libraries needed!)

```bash
# Extract environment
./pixi-unpack env.tar -o /app

# Compile (using bundled compiler)
env/bin/c++ -o myapp main.cpp -I env/include -L env/lib -lzstd -Wl,-rpath,\$ORIGIN/env/lib

# Run (libraries are bundled)
LD_LIBRARY_PATH=env/lib ./myapp
```

## Archive Size

~142 MB (includes GCC compiler, zstd, and all dependencies)
