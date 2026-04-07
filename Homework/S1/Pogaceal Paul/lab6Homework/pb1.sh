#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <source_file>"
    echo "Example: $0 example.c"
    exit 1
fi

file=$1

if [ ! -f "$file" ]; then
    echo "Error: File '$file' does not exist."
    exit 1
fi

functions=$(grep "(" $file | grep -v ";" | cut -d'(' -f1 | cut -d' ' -f2)

for func in $functions
do
    calls=$(grep -n "$func" $file | grep -v ":[a-zA-Z]")
    
    if [ -z "$calls" ]
    then
        echo "Function $func is called 0 times."
    else
        count=$(echo "$calls" | wc -l)
        lines=$(echo "$calls" | cut -d':' -f1 | tr '\n' ' ')
        
        echo "Function $func is called $count times at line(s): $lines"
    fi
done