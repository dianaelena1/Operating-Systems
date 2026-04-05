#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Try 2 files $0 <file1> <file2>"
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "File '$1' does not exist"
    exit 1
fi

if [ ! -f "$2" ]; then
    echo "File '$2' does not exist"
    exit 1
fi


diff --side-by-side --suppress-common-lines "$1" "$2" | head -n 3