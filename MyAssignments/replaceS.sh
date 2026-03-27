#!/bin/bash

# check if at least two arguments are provided (letter + 1 file)
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <lowercase_letter> <file1> [file2 ...]"
    exit 1
fi

LETTER=$1
shift # remove the letter from the argument list, leaving only filenames

for FILE in "$@"; do
    if [ -f "$FILE" ]; then
        # replaces characters that are NOT letters, numbers, or whitespace
        # use -i to edit the file in-place
        sed -i "s/[^a-zA-Z0-9[:space:]]/$LETTER/g" "$FILE"
        echo "Processed: $FILE"
    else
        echo "Skip: $FILE (File not found)"
    fi
done