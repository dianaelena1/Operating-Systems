#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Utilizare: $0 fisier1 fisier2 ..."
    exit 1
fi

for fisier in "$@"; do
    if [ ! -f "$fisier" ]; then
        echo "Fișierul $fisier nu există."
        continue
    fi

    echo "-Rezultate pentru: $fisier -"

    nr_linie=0
    while IFS= read -r linie; do
        ((nr_linie++))

        duplicat=$(echo "$linie" | awk '{
            for (i=1; i<NF; i++) {
                if ($i == $(i+1)) {
                    print $i
                    exit
                }
            }
        }')

        if [ -n "$duplicat" ]; then
            echo "$nr_linie $duplicat: $linie"
        fi

    done < "$fisier"
    echo ""
done