#!/bin/bash

letter=$1

shift

for file in "$@"
do
    if [ -f "$file" ]; then
        sed -i "s/[a-z]/${letter}&/g" "$file"
        echo "Processed $file"
    else
        echo "Error: $file not found."
    fi
done