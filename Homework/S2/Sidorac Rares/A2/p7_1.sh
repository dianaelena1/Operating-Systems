#!/bin/bash

if [ $# -eq 0 ]; then
    echo "use: $0 [file1] [file2] ..."
    exit 1
fi


for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' does not exist"
        continue
    fi
    

    sed -i 'y/aeiou/AEIOU/' "$file"
    
done
