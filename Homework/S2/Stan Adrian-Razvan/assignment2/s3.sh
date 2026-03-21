#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Error: You must provide a word followed by at least one file."
    exit 1
fi

TARGET_WORD=$1

shift

for FILE in "$@"; do
    if [ -f "$FILE" ]; then
        sed -i "/$TARGET_WORD/d" "$FILE"
        echo "Cleaned up: $FILE"
    else
        echo "Warning: File '$FILE' does not exist."
    fi
done

#cd "Operating-Systems/Homework/S2/Stan Adrian/assignment2"
#chmod +x s3.sh
#echo "Ana are mere" > text1.txt
#echo "Ana are pere" >> text1.txt
#echo "Mai multe mere" >> text1.txt

#echo "Niciun fruct" > text2.txt
#echo "Doar mere" >> text2.txt

#./s3.sh "mere" text1.txt text2.txt