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
        # creates the search pattern. it creates six distinct capture groups
        # \1 leading spaces/punctuation
        # \2 the first word
        # \3 first separator
        # \4 second word
        # \5 second separator
        # \6 third word
        SEARCH_PATTERN="${START}${WORD}${SEPARATOR}${WORD}${SEPARATOR}${WORD}"

        # defines the replacement string using the capture group references
        # reconstructs the beginning of the line as
        # start + third word + sep 1 + second word + sep 2 + first word
        REPLACE_PATTERN="\1\6\3\4\5\2"

        # stream editor (sed) command to apply the changes to the file
        # -E enables extended regular expressions
        # -i stands for "in-place". it tells sed to save the modifications back to the original file
        # s/${SEARCH_PATTERN}/${REPLACE_PATTERN}/ this is sed's substitute command
        sed -E -i "s/${SEARCH_PATTERN}/${REPLACE_PATTERN}/" "$file"
        echo "Processed: $file"
    else
        echo "Skipped: $file not found."
    fi
done