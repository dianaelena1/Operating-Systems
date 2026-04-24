#!/bin/bash


max_words=0
max_file=""

for file in "$@"; do
    word_count=$(wc -w < "$file")
    
    if [ "$word_count" -gt "$max_words" ]; then
        max_words=$word_count
        max_file=$file
    fi
done

echo "$max_file $max_words"
