#!/bin/bash

if [ $# -eq 0 ]
then
    echo "Error: You must provide at least one file name."
    exit 1
fi

for FILE in "$@"
do
    if [ -f "$FILE" ]
    then
        echo "--- Analyzing $FILE ---"

        LINE_NUM=1

        while IFS= read -r line
        do
            if [ ${#line} -gt 20 ]
            then
                words=($line)

                if [ ${#words[@]} -gt 0 ]
                then
                    FIRST_WORD=${words[0]}

                    LAST_INDEX=$(( ${#words[@]} - 1 ))
                    LAST_WORD=${words[$LAST_INDEX]}

                    echo "Line $LINE_NUM: First Word = '$FIRST_WORD', Last Word = '$LAST_WORD'"
                fi
            fi

            LINE_NUM=$(( LINE_NUM + 1 ))

        done < "$FILE"

    else
        echo "Warning: $FILE does not exist or is not a regular file."
    fi
done