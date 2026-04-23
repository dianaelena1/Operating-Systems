#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Args: file1 file2 ... directory"
    exit 1
fi

dir="${@: -1}"
files=("${@:1:$#-1}")

if [ ! -d "$dir" ]; then
    echo "Directory not found: $dir"
    exit 1
fi

for fname in "${files[@]}"
do
    echo "File: $fname"

    find "$dir" -type f -name "$fname" 2>/dev/null | while read path
    do
        subdir=$(dirname "$path")

        stat -c "%W $subdir" "$subdir"
    done | sort -nr | awk '{print $2}' | uniq
done