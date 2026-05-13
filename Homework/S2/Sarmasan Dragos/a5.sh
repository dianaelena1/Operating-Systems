#!/bin/bash
 
if [ "$#" -ne 2 ] || [ ! -d "$1" ] || [ ! -d "$2" ]; then
    exit 1
fi
 
mv "$2" "$1"
 
find "$1/$(basename "$2")" -type f -exec mv {} {}.unu \;