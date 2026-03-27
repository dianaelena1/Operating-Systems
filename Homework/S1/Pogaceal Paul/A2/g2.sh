#!/bin/bash

# Need a word to search for and at least one file
if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <word_to_find> <file1> [<file2> ...]"
    exit 1
fi

WORD=$1
shift # Keep only the filenames

MATCH_COUNT=0

for FILE in "$@"; do
    if [ -f "$FILE" ]; then
        # grep -q quietly checks if the word exists without printing the lines
        if grep -q "$WORD" "$FILE"; then
            echo "$FILE"
            MATCH_COUNT=$((MATCH_COUNT + 1))
        fi
    else
        echo "Couldn't find '$FILE'."
    fi
done

echo "Total files with the word: $MATCH_COUNT"