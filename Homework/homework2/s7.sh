#!/bin/bash

for file in "$@"
do
    if [ ! -f "$file" ]; then
        echo "File does not exist: $file"
        continue
    fi

    sed 's/a/A/g; s/e/E/g; s/i/I/g; s/o/O/g; s/u/U/g' "$file"
    echo
done