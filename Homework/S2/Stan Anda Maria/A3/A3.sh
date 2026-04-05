#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Utilizare: $0 fisier1 fisier2 ..."
    echo "Eroare: Nu a fost furnizat niciun fisier pentru analiza."
    exit 1
fi

if ! command -v awk &> /dev/null; then
    echo "Eroare: Utilitarul 'awk' nu a fost gasit. Scriptul nu poate rula."
    exit 1
fi


for fisier in "$@"
do
    if [ ! -f "$fisier" ]; then
        echo "Avertisment: '$fisier' nu exista sau nu este un fisier obisnuit. Sarim peste el."
        continue
    fi

    if [ ! -r "$fisier" ]; then
        echo "Avertisment: Nu am permisiuni de citire pentru '$fisier'."
        continue
    fi

    echo "--- Rezultate pentru: $fisier ---"

    awk '{
        split("", frecventa);
        for (i = 1; i <= NF; i++) {
            frecventa[$i]++;
        }
        for (cuvant in frecventa) {
            if (frecventa[cuvant] >= 2) {
                printf "  [Linia %d]: cuvantul \"%s\" apare de %d ori\n", NR, cuvant, frecventa[cuvant];
            }
        }
    }' "$fisier"

    echo ""
done