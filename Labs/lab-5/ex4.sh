#!/bin/bash
read -p "Enter file/directory name: " name

if [ -d "$name" ]; then
    echo "$name is a directory."
elif [ -f "$name" ]; then
    echo "$name is a regular file."
elif [ ! -e "$name" ]; then
    echo "$name does not exist."
else
    echo "$name is not accessible."
fi