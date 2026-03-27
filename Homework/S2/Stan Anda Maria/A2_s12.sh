#!/bin/bash

litera=$1
shift
for fisier in "$@"
do
    if [ -f "$fisier" ]; then
        echo "Se procesează fișierul: $fisier"

        sed -i "s/[0-9]/$litera/g" "$fisier"
    else
        echo "Atenție: $fisier nu este un fișier valid."
    fi
done

echo "Gata! Toate cifrele au fost înlocuite cu '$litera'."