# Huffman compressor / decompressor (C++)
This repo contains a simple Huffman coding compressor and decompressor written in C++.

Features:
- Optimized encoding with pre-computed codes (150x speedup)
- Bit-level I/O for efficient storage
- Comparable decompression speeds to gzip on small files

Build

    - Requires g++ with C++11. Using msys/MinGW on Windows or standard g++ on Linux/macOS.
    - Using Make:
        - make
    - Or compile manually:
        - g++ -std=c++11 compress.cpp Helper.cpp HCTree.cpp -o compress
        - g++ -std=c++11 uncompress.cpp Helper.cpp HCTree.cpp -o uncompress
Usage

    - Compress:
        - ./compress input-file output-file
    - Uncompress:
        - ./uncompress compressed-file output-file
Format

    - The compressed file contains:
        - 4-byte int: original file size
        - 256 × 4-byte ints: frequency table for bytes 0..255
        - Remaining bytes: compressed bitstream (MSB-first within each byte)

