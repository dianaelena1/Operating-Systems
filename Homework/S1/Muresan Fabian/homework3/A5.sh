#!/bin/bash
if [ "$#" -lt 1 ]; then
    echo "Usage: $0 file1 [file2 ...]"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist."
        continue
    fi

    echo "--- Results for $file ---"
    line_num=1
    
    while IFS= read -r line || [ -n "$line" ]; do
        if [ "${#line}" -gt 20 ]; then
            
            read -ra words <<< "$line"
            
            if [ "${#words[@]}" -gt 0 ]; then
                first="${words[0]}"
                last="${words[-1]}" 
                echo "Line $line_num: $first $last"
            fi
        fi
        
        line_num=$((line_num + 1))
    done < "$file"
done