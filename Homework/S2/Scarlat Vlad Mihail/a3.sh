#!/bin/sh

for file in "$@"
do
    line_no=1

    while read line
    do
        word=$(echo "$line" | awk '{
            for(i=1;i<NF;i++)
                if($i == $(i+1)) {
                    print $i
                    exit
                }
        }')

        if [ -n "$word" ]; then
            echo "$file: line $line_no: [$word] $line"
        fi

        line_no=$((line_no + 1))
    done < "$file"
done