#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File not found: $file"
        continue
    fi

    echo "Processing file: $file"

    line_number=0
    while IFS= read -r line; do
        ((line_number++))

        if [ ${#line} -gt 20 ]; then
            first_word=$(echo "$line" | awk '{print $1}')
            last_word=$(echo "$line" | awk '{print $NF}')

            echo "Line $line_number: $first_word ... $last_word"
        fi
    done < "$file"

done