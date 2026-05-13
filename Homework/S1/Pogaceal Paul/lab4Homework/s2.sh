#!/bin/bash

# Need at least the text to find and one file
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <text_to_delete> <file1> [<file2> ...]"
    exit 1
fi

TEXT=$1
shift # Drop the text argument so we're left with just the filenames

for FILE in "$@"; do
    if [ -f "$FILE" ]; then
        # grep -v keeps lines that DON'T match. Save to a temp file, then overwrite.
        #grep -v "$TEXT" "$FILE" > tmp_file && mv tmp_file "$FILE"
        sed -i "s/$TEXT/ /g" "$FILE"
        echo "Cleaned up: $FILE"
    else
        echo "Oops, couldn't find '$FILE'."
    fi
done