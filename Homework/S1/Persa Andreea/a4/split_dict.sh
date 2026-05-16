#!/bin/bash

# Check if a filename was provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <input_file>"
    exit 1
fi

INPUT_FILE=$1
OUTPUT_DIR="dictionary_output"

# Create the directory, or clear it if it already exists
mkdir -p "$OUTPUT_DIR"
rm -f "$OUTPUT_DIR"/*.txt

echo "Processing $INPUT_FILE..."

for char in {A..Z}; do

    grep -oi "\b$char[a-z']*" "$INPUT_FILE" | sort -uf > "$OUTPUT_DIR/${char}.txt"

    echo "Generated ${char}.txt"
done

echo "Done! You can find the files in the '$OUTPUT_DIR' folder."