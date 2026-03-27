#!/bin/bash

text=$1

shift

for file in "$@"
do
    sed -i "/$text/d" "$file"

    echo "Done cleaning $file"
done