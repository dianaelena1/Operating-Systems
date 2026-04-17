#!/bin/bash

num_files=$#
total_words=0

for file in "$@"
do
  # words=$(wc -w <"$file")
  words=$(awk '{total += NF} END {print total}' "$file")
  total_words=$((total_words + words))
done

avg=0
if [ $num_files -gt 0 ]; then
  avg=$((total_words / num_files))
fi

echo "Number of files: $num_files"
echo "Total word: $total_words"
echo "Average words per file: $avg"


