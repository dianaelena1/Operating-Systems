#!/bin/bash

# s9)
for file in "$@"; do
  if [[ -f "$file" ]]; then

    # 2nd and 4th words are set to empty, then we rebuild the file without those words
    awk '{$2=$4=""; $1=$1}1'  "$file"
  fi
done