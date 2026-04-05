#!/bin/bash

if [ $# -eq 0 ]
then
  echo "Error: You must enter a username as a parameter"
  exit 1
fi

USERNAME=$1

SECTION=${USERNAME:2:2}
echo "Section: $SECTION"

SUM=0

LEN=${#USERNAME}

for (( i=0; i<$LEN; i++ ))
do
  CHAR=${USERNAME:$i:1}

case "$CHAR" in
  -[0-9]|[0-9])
    SUM=$((SUM + CHAR))
    ;;
  esac
done

echo "Sum of digits: $SUM"