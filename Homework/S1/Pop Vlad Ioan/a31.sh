#!/bin/bash

if [ $# -lt 2 ]
then
    echo "Error: You must provide a lowercase letter followed by at least one file name."
    exit 1
fi

LETTER=$1

case "$LETTER" in
    [a-z])
        ;;
    *)
        echo "Error: The first parameter MUST be a single lowercase letter."
        exit 1
        ;;
esac

shift

for FILE in "$@"
do
    if [ -f "$FILE" ]
    then
        echo "--- Replacing specials in $FILE ---"
        sed "s/[^a-zA-Z0-9 $(printf '\t')]/$LETTER/g" "$FILE"
    else
        echo "Warning: $FILE does not exist."
    fi
done