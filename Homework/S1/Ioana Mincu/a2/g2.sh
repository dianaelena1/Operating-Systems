#!/bin/bash

word=$1

shift

count=0

echo "Files containing the word '$word':"

for file in "$@"
do
    if grep -q "$word" "$file"
    then
        echo "$file"
        count=$((count + 1))
    fi
done

echo "Total number of files: $count"