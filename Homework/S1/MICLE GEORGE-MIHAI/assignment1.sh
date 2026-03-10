#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <directory_name>"
    exit 1
fi

TARGET_DIR=$1

if [ ! -d "$TARGET_DIR" ]; then
    echo "Error: Directory '$TARGET_DIR' does not exist."
    exit 1
fi

for FILE in "$TARGET_DIR"/*; do
    if [ -f "$FILE" ]; then
        if file "$FILE" | grep -q "ASCII text"; then
            echo "-----------------------------------"
            echo "Filename: $FILE"
            echo "First 3 lines:"
            head -n 3 "$FILE"
            echo ""
        fi
        
    fi
done