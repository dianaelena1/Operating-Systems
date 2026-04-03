#!/bin/bash

if [ $# -eq 0 ]; then
     echo "Error: Please provide at least one filename."
     echo "Usage: $0 <filename1> <filename2> ..."
     exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' doesn't exit."
        continue
    fi

    cut -d' ' -f1,3,5- "$file" > "$file.tmp"
    mv "$file.tmp" "$file"
    echo "Removed 2nd and 4th words from '$file'."
done