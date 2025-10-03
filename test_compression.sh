#!/bin/bash

for file in test_files/*; do
    echo "Testing: $file"
    
    time ./compress $file $file.myzip
    
    # Comparison
    time gzip -k $file
    
    # Show sizes
    ls -lh $file*
    echo "---"
done