#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <input_file>"
    exit 1 
fi

input_file="$1"

if [ ! -f "$input_file" ]; then
    echo "Error: File '$input_file' not found."
    exit 1
fi

target_dir="dictionary_output"
mkdir "$target_dir"

echo "Extracting words and building dictionaries..."

for letter in {A..Z}; do
    grep -i -o "\<$letter[a-zA-Z]*\>" "$input_file" | sort -f > "$target_dir/$letter.txt"
done

echo "Done! The dictionary files have been created in the '$target_dir' directory."
