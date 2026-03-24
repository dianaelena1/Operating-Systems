#!/bin/bash

fisier_lista=$1

if [ ! -f "$fisier_lista" ]; then
    echo "Eroare: Fișierul listă $fisier_lista nu există!"
    exit 1
fi

shift

while IFS= read -r nume_de_sters || [ -n "$nume_de_sters" ]; do
    for director in "$@"; do
        if [ -d "$director" ]; then
            echo "Caut și șterg '$nume_de_sters' în: $director"

            find "$director" -type f -name "$nume_de_sters" -delete
        else
            echo "Atenție: $director nu este un director valid."
        fi
    done
done < "$fisier_lista"

echo "Operațiune finalizată."