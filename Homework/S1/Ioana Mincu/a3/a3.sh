#!/bin/bash

for file in "$@"
do
    if [[ -f "$file" ]]; then
        awk 'length($0) > 10 {
                count++;
                print NR ": " substr($0, 11)
             }
             END {
                print "File: " FILENAME ". Lines displayed: " count
             }' "$file"
    else
        echo "Skip: $file not found."
    fi
done