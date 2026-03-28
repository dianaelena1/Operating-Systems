#!/bin/bash

for fisier in "$@"
do
    if [ -f "$fisier" ]; then
        echo "Analizam fisierul: $fisier "
        nr_linie=1
        while read -r linie || [ -n "$linie" ]
        do
            cuvinte_unice=$(echo "$linie" | tr -s ' ' '\n' | sort -u)

            for cuvant in $cuvinte_unice
            do
                [ -z "$cuvant" ] && continue

                aparitii=$(echo "$linie" | grep -o -w "$cuvant" | wc -l)

                if [ "$aparitii" -ge 2 ]; then
                    echo "Linia $nr_linie: cuvantul '$cuvant' apare de $aparitii ori."
                fi
            done
            ((nr_linie++))
        done < "$fisier"
    fi
done