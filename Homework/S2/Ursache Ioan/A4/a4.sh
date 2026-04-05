#!/bin/bash

# 4. Given a list of filenames and a directory name, write a Shell script that prints for each file
# all the subdirectories in which it appears.
# Print these subdirectories sorted in decreasing order of the creation date and time.

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <search_directory> <filename1> [filename2 ...]"
    exit 1
fi

SEARCH_DIR="$1"
shift

for FILE_NAME in "$@"; do
    echo "--- Searching for file: $FILE_NAME ---"

    find "$SEARCH_DIR" -type f -name "$FILE_NAME" -exec dirname {} \; | \
    xargs -I {} stat -c "%W %n" "{}" 2>/dev/null | \
    sort -rn | \
    cut -d' ' -f2-

    echo ""
done