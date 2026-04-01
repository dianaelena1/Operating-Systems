#!/bin/bash


if [ -z "$1" ] || [ ! -d "$1" ]; then
    echo "Eroare: introdu un nume de director valid."
    exit 1
fi


total=$(find "$1" -type f -exec cat {} + | wc -l)

echo "Numărul total de linii este: $total"


