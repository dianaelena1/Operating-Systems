#!/bin/bash


for file in "$@"; do
  if [[ -f "$file" ]]; then
    
    # 2nd and 4th words are set to empty, then we rebuilds the file without those words 
    awk '{$2=$4=""}1'  "$file"
  fi
done