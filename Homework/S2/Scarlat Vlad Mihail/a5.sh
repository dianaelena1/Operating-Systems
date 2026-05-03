#!/bin/sh

dir1=$1
dir2=$2

mv "$dir2" "$dir1"

find "$dir1/$(basename "$dir2")" -type f | while read file
do
    mv "$file" "$file.unu"
done