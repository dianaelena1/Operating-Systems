#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Usage: $0 not enough arguments!"
    exit 1
fi

text="$1"
shift 

for file in "$@"; do
    if [ -f "$file" ]; then
        sed -i '' "1a\\
$text
" "$file"
    else
        echo "Skipping $file its not a file!"
    fi
done
