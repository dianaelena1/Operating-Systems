#!/bin/bash
 
for file in "$@"; do
    count=0; n=0
    while IFS= read -r line; do
        ((++n))
        [ ${#line} -gt 10 ] && echo "Line $n: ${line:10}" && ((count++))
    
        done < "$file"
    echo "$file has $count lines displayed"
done
 