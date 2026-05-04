#!/bin/bash

# defines a "word", defined as one or more (+) alphanumeric characters(letters a-z, A-Z, or numbers 0-9)
WORD="([a-zA-Z0-9]+)"

# defines a "separator", defined as one or more characters that are not (^) alphanumeric (spaces, punctuations, tabs, etc.)
SEPARATOR="([^a-zA-Z0-9]+)"

# defines a pattern that anchors to the very beginning of a line (^) and matches zero or more (*) non-alphanumeric characters (captures any leading indentation or punctuation before the first actual word)\
START="^([^a-zA-Z0-9]*)"

# starts a loop that iterates over every argument passed to the script viat the command line ("$@" all arguments)
for file in "$@"
do
    # checks if the argument ($file) actually exists and is a regular file (not a directory)
    if [ -f "$file" ]; then
        
        SEARCH_PATTERN="${START}${WORD}${SEPARATOR}${WORD}${SEPARATOR}${WORD}"

        
        REPLACE_PATTERN="\1\6\3\4\5\2"

        sed -E -i "s/${SEARCH_PATTERN}/${REPLACE_PATTERN}/" "$file"
        echo "Processed: $file"
    else
        echo "Skipped: $file not found."
    fi
done