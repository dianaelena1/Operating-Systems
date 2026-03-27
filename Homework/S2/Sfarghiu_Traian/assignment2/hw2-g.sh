#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "'$file' is not a regular file, skipping."
        continue
    fi

    grep -v '[a-zA-Z0-9]' "$file"
done
