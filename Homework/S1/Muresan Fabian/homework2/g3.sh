#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 dir1 [dir2 ...]"
    exit 1
fi

for dir in "$@"; do
    
    if [ ! -d "$dir" ]; then
        echo "Warning: '$dir' is not a valid directory. Skipping..."
        continue
    fi
    
    echo "Scanning directory: $dir"
    
    find "$dir" -type f | while IFS= read -r file; do
        
        if file -b --mime-encoding "$file" | grep -q "binary"; then
            echo "Binary file: $file"
        fi
        
    done
done