#!/bin/bash

if [ "$#" -lt 2 ]; then
  echo:"Error: You must provide at least 2 file names"
  exit 1
fi

for FILE in "$@"; do
  if [ -f "$FILE" ]; then
    echo "$FILE"
    awk 'length($0) > 20 {print NR, $1, $NF}' "$FILE"
  else
    echo "Warning: File '$FILE' does not exist"
  fi
done