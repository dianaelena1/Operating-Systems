#!/bin/bash

for file in "$@"; do
    if [[ -f "$file" ]]; then
        
        awk '
            length($0) > 10 {
                print FNR, substr($0, 11)
                count++
            }
            END {
                print FILENAME, count + 0
            }
        ' "$file"
        
    else
        echo "Error: File '$file' does not exist."
    fi
done
