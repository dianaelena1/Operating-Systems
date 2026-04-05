#!/bin/bash

for file in "$@"
do
    if [ ! -f "$file" ]; then
        echo "File does not exist: $file"
        continue
    fi

    awk '
    {
        delete count

        for(i = 1; i <= NF; i++) {
            count[$i]++    
        }    

        for(word in count) {
            if(count[word] >= 2) {
                printf("File: %s, Line: %d, Word: %s\n", FILENAME, NR, word)
            }
        }
    }
    ' "$file"

done