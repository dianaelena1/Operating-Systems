#!/bin/bash

if [ -z "$1" ]; then
    echo "Please provide one input file"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "The given argument is not a file"
    exit 1
fi

    file="$1"

    globals=$(grep -E "^(int|char|float|double|long|short|unsigned|signed)[ \t]" "$file" | \
            grep -v "(" | \
            sed -E "s/([^[;=]+).*/\1/" | \
            awk '{print $NF}' | \
            tr -d '*[]')

    for var in $globals; do
        count=$(grep -E -o "\<$var\>" "$file" | wc -l)
        
        lines=$(grep -E -n "\<$var\>" "$file" | cut -d: -f1 | tr '\n' ' ')
        
        echo "Global variable '$var' appears $count times."
        echo "Lines: $lines"
    done