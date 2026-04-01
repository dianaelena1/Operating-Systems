#!/bin/bash

if [ "$#" -eq 0 ]; then
    echo "Insert at least one file name"
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File $file not found or not a regular file"
        continue
    fi

    read -r sum l1 l2 < <(awk '
        BEGIN { 
            sum = 0 
            l1 = 0 
            l2 = 0 
        }
        {
            if ($0 ~ /[0-9]/) {
                l1++
                gsub(/[^0-9]+/, " ", $0)
                
                for (i = 1; i <= NF; i++) {
                    sum += $i
                }
            } else {
                l2++
            }
        }
        END {
            print sum, l1, l2
        }
    ' "$file")

    echo "$file sum = $sum l1/l2 = ${l1}/${l2}"
done