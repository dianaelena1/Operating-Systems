#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Utilizare: $0 <director_destinatie> <director_sursa>"
    exit 1
fi

dir_dest=$1
dir_sursa=$2

if [ ! -d "$dir_dest" ]; then
    echo "Directorul destinatie '$dir_dest' nu exista."
    exit 1
fi

if [ ! -d "$dir_sursa" ]; then
    echo "Directorul sursa '$dir_sursa' nu exista."
    exit 1
fi


find "$dir_sursa" -type f | while read -r fisier; do
    mv "$fisier" "${fisier}.unu"
done

mv "$dir_sursa" "$dir_dest"

echo "Operațiune finalizată cu succes!"