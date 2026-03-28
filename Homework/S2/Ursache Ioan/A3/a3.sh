#!/bin/bash

# Write a shell script which takes as parameters two words followed by several file names.
# The script will replace any occurrence of the first word with the second word in each line of the given files.

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <search> <replace> [files...]"
    exit 1
fi

oldWord=$1
newWord=$2
shift 2

if [ "$#" -gt 0 ]; then
    for file in "$@"; do
        [ -f "$file" ] && sed -i "s/$oldWord/$newWord/g" "$file"
    done
else
    sed "s/$oldWord/$newWord/g"
fi