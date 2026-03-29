#!/bin/bash

# Check if any parameters were passed
if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 file2 ..."
    exit 1
fi

num_files=$#
total_words=0

# Loop through every file provided
for file in "$@"; do
    if [ -f "$file" ]; then
        count=$(wc -w < "$file")
        total_words=$((total_words + count))
    else
        echo "Warning: $file is not a regular file. Skipping."
        num_files=$((num_files - 1))
    fi
done

# Check to avoid division by zero if no valid files were found
if [ $num_files -gt 0 ]; then
    average=$((total_words / num_files))

    echo "Number of files: $num_files"
    echo "Total word count: $total_words"
    echo "Average words per file: $average"
else
    echo "No valid files were processed."
fi