#!/bin/bash
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 word file1 [file2 ...]"
    exit 1
fi

word=$1

shift 

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi
    
    sed -i "/$word/d" "$file"
    echo "Processed '$file'."
done