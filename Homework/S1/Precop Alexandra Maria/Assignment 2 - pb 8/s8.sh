#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 file1 [file2 ...]"
  exit 1
fi

for file in "$@"; do
  if [ -f "$file" ]; then
    echo "Processing $file..."
    # sed -i -E 's/^([^:]+)(:[^:]+:)([^:]+)/\3\2\3/' "$file"
    sed -i -E 's/^([^:]+)(:[^:]+):[^:]+/\1\2:\1/' "$file"
  else
    echo "Error: $file not found"
  fi
done