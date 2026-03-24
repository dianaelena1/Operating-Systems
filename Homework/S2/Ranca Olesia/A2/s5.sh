#!/bin/bash

# verificare parametri
if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 file2 ..."
    exit 1
fi

for file in "$@"; do
    if [ -f "$file" ]; then
        # elimină cuvintele care conțin cifre
        sed -E -i 's/\b[[:alnum:]]*[0-9][[:alnum:]]*\b//g' "$file"
        echo "Processed $file"
    else
        echo "$file is not a valid file"
    fi
done
