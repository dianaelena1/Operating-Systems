#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 file1 [file2 ...] directory"
    exit 1
fi

dir="${@: -1}"

if [ ! -d "$dir" ]; then
    echo "Last argument must be a directory"
    exit 1
fi

files=("${@:1:$#-1}")

for fname in "${files[@]}"; do
    echo "File: $fname"

    found=0

    find "$dir" -type f -name "$fname" 2>/dev/null | while read f; do
        found=1
        size=$(stat -f%z "$f")
        dirpath=$(dirname "$f")
        echo "$size $dirpath"
    done | sort -nr | while read size path; do
        echo "  $path (size=$size)"
    done

    if ! find "$dir" -type f -name "$fname" | grep -q .; then
        echo "  Not found"
    fi

    echo
done
