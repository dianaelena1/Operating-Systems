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

    results=$(find "$dir" -type f -name "$fname" 2>/dev/null)

    if [ -z "$results" ]; then
        echo "  Not found"
        continue
    fi

    for f in $results; do
        size=$(stat -f%z "$f")
        dirpath=$(dirname "$f")
        echo "$size $dirpath"
    done | sort -nr | while read size path; do
        echo "  $path (size=$size)"
    done

    echo
done
