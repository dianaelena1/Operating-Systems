#!/bin/bash

# Check that exactly one argument was provided
if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

directory="$1"

# Check if the directory exists
if [[ ! -d "$directory" ]]; then
    echo "Error: '$directory' is not a valid directory."
    exit 1
fi

# Function to count the maximum number of repeating lines in a file
count_max_repeating_lines() {
    local file="$1"
    local max_count=0
    local current_count=1
    local prev_line=""
    
    # Read the file line by line
    while IFS= read -r line || [[ -n "$line" ]]; do
        if [[ "$line" == "$prev_line" ]]; then
            current_count=$((current_count + 1))
            if [[ $current_count -gt $max_count ]]; then
                max_count=$current_count
            fi
        else
            current_count=1
            prev_line="$line"
        fi
    done < "$file"
    
    echo "$max_count"
}

# Recursively find and list all files and directories
find "$directory" -print | sort | while read -r item; do
    rel_path="${item#$directory}"
    rel_path="${rel_path#/}"
    
    # Skip the root directory itself
    if [[ -z "$rel_path" ]]; then
        continue
    fi
    
    # Check if it's a file or directory
    if [[ -f "$item" ]]; then
        max_repeating=$(count_max_repeating_lines "$item")
        echo "[FILE] $rel_path - Max repeating lines: $max_repeating"
    elif [[ -d "$item" ]]; then
        echo "[DIR]  $rel_path"
    fi
done

