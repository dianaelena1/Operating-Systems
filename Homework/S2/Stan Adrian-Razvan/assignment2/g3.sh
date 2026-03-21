#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Error: You must provide at least one directory name."
    exit 1
fi

for DIR in "$@"; do
    if [ -d "$DIR" ]; then
        echo "--- Binaries found in: $DIR ---"
        find "$DIR" -type f -exec file {} \; | grep -v "text" | cut -d: -f1
    else
        echo "Warning: Directory '$DIR' does not exist."
    fi
done

#chmod +x g3.sh

#mkdir folderA
#mkdir folderB

#cp /usr/bin/ls.exe ./folderA/secret_binary

#echo "Aici avem un text" > ./folderB/normal_file.txt

#./g3.sh folderA folderB