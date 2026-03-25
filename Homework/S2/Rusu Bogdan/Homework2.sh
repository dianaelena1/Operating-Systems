#!/bin/bash

WORD="([a-zA-Z0-9]+)"

SEPARATOR="([^a-zA-Z0-9]+)"

START="^([^a-zA-Z0-9]*)"

for file in "$@"
do
    if [ -f "$file" ]; then
        SEARCH_PATTERN="${START}${WORD}${SEPARATOR}${WORD}${SEPARATOR}${WORD}"
        REPLACE_PATTERN="\1\6\3\4\5\2"
        sed -E -i "s/${SEARCH_PATTERN}/${REPLACE_PATTERN}/" "$file"
        echo "Processed: $file"
    else
        echo "Skipped: $file not found."
    fi
done