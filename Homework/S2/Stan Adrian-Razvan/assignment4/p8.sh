#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Error: You must provide exactly one C++ file."
    exit 1
fi

FILE=$1

if [ ! -f "$FILE" ]; then
    echo "Error: File '$FILE' does not exist."
    exit 1
fi

CLASSES=$(grep -E '^\s*class ' "$FILE" | awk '{print $2}' | tr -d '{:')

for CLASS in $CLASSES; do
    echo "Class: $CLASS"

    LINES=$(grep -n -w "new $CLASS" "$FILE" | cut -d: -f1)
    COUNT=$(grep -w "new $CLASS" "$FILE" | wc -l)

    if [ "$COUNT" -gt 0 ]; then
        echo "Total instances created: $COUNT"
        echo "Line numbers: $LINES"
    else
        echo "No instances created using 'new'."
    fi
done