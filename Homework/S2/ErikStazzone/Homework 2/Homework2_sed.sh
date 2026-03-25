#!/bin/bash

if [ "$#" -lt 2 ]; then
    exit 1
fi

file=$1

shift

for word in "$@"; do
    sed -i "s/\b$word\b//g" "$file"
done

echo "occurences removed from $file."