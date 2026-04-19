#!/bin/bash

if [ $# -lt 3 ]; then
  echo "Usage: $0 word to find, word to replace, file1 [file2 ...]"
  exit 1
fi

find_word=$1
replace_word=$2

shift 2

for file in "$@"; do
  if [ -f "$file" ]; then
    echo "Processing $file..."
    awk "{ gsub(/$find_word/, \"$replace_word\"); print }" "$file" | mv "$file.tmp" "$file"
    echo "Processed!"
  else
    echo "Error: $file not found, skipping..."
  fi
done

echo "Done! (^u^)"