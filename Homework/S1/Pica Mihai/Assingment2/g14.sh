#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 not enough arguments!"
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        grep '^[A-Z]\+$' "$file"
    else
        echo "Skipping $file is not a file!"
    fi
done
