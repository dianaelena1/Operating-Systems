#!/bin/bash

# Problem S4.
# Write a shell script which takes as parameters an uppercase letter followed by several file names.
# The script will add the given letter in the front of each lowercase on each line in all given files.

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <UPPERCASE_LETTER> <file1> [file2 ...]"
    exit 1
fi

LETTER=$1

if [[ "$LETTER" != [A-Z] ]]; then
    echo "LETTER IS NOT UPPERCASE"
    exit 1
fi

shift

for file in "$@"; do
    if [ -f "$file" ]; then
        temp_file="${file}.tmp"
        : > "$temp_file"

        while IFS= read -r line || [ -n "$line" ]; do
            new_line=""

            for (( i=0; i<${#line}; i++ )); do
                char="${line:$i:1}"

                if [[ "$char" == [a-z] ]]; then
                    new_line="${new_line}${LETTER}${char}"
                else
                    new_line="${new_line}${char}"
                fi
            done

            echo "$new_line" >> "$temp_file"
        done < "$file"

        mv "$temp_file" "$file"
        echo "Processed: $file"
    else
        echo "Error: $file not found."
    fi
done