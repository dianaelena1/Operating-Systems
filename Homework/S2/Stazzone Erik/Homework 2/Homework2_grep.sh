#!/bin/bash

if [ "$#" -ne 1 ]; then
    exit 1
fi

dir=$1

if [ ! -d "$dir" ]; then
    echo "$dir is not a valid directory."
    exit 1
fi

find "$dir" -type f -name "*.txt" -exec cat {} +