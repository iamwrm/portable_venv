#include <iostream>
#include <vector>
#include <cstring>
#include <zstd.h>

int main() {
    // Print zstd version
    std::cout << "ZSTD Version: " << ZSTD_versionString() << std::endl;
    
    // Original data
    const char* original = "Hello, this is a test string for zstd compression! "
                           "We repeat it several times to make compression worthwhile. "
                           "Hello, this is a test string for zstd compression! "
                           "We repeat it several times to make compression worthwhile. "
                           "Hello, this is a test string for zstd compression!";
    size_t originalSize = strlen(original);
    
    // Compress
    size_t compressBound = ZSTD_compressBound(originalSize);
    std::vector<char> compressed(compressBound);
    
    size_t compressedSize = ZSTD_compress(
        compressed.data(), compressBound,
        original, originalSize,
        1  // compression level
    );
    
    if (ZSTD_isError(compressedSize)) {
        std::cerr << "Compression error: " << ZSTD_getErrorName(compressedSize) << std::endl;
        return 1;
    }
    
    std::cout << "Original size: " << originalSize << " bytes" << std::endl;
    std::cout << "Compressed size: " << compressedSize << " bytes" << std::endl;
    std::cout << "Compression ratio: " << (double)originalSize / compressedSize << "x" << std::endl;
    
    // Decompress
    size_t decompressedSize = ZSTD_getFrameContentSize(compressed.data(), compressedSize);
    std::vector<char> decompressed(decompressedSize + 1);
    
    size_t result = ZSTD_decompress(
        decompressed.data(), decompressedSize,
        compressed.data(), compressedSize
    );
    
    if (ZSTD_isError(result)) {
        std::cerr << "Decompression error: " << ZSTD_getErrorName(result) << std::endl;
        return 1;
    }
    
    decompressed[decompressedSize] = '\0';
    
    // Verify
    if (strcmp(original, decompressed.data()) == 0) {
        std::cout << "Success! Decompressed data matches original." << std::endl;
    } else {
        std::cerr << "Error: Decompressed data doesn't match!" << std::endl;
        return 1;
    }
    
    return 0;
}
