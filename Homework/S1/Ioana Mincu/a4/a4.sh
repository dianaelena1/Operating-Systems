#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <cpp_file>"
    exit 1
fi

cpp_file=$1

class_names=$(grep -E "^class|^struct" "$cpp_file" | awk '{print $2}' | sed 's/[:{]//g')

for class in $class_names; do
    echo "Class: $class"

    instances=$(grep -nE "new +$class|\<$class\> +[a-zA-Z0-9_]+" "$cpp_file")

    if [ -n "$instances" ]; then
        echo "$instances"

        count=$(echo "$instances" | wc -l)
        echo "Total instances found: $count"
    else
        echo "No instances found."
    fi
    echo ""
done