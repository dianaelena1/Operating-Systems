#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Utilizare: $0 <fisier_initial> <fisier_summer_grades>"
    exit 1
fi

INITIAL_FILE="$1"
SUMMER_FILE="$2"

if [ ! -f "$INITIAL_FILE" ] || [ ! -f "$SUMMER_FILE" ]; then
    echo "Eroare: Fisierele nu exista."
    exit 1
fi

TEMP_FILE="temp_calc.txt"
> "$TEMP_FILE"

while read -r nume prenume medie_iarna || [ -n "$medie_iarna" ]; do
    [ -z "$nume" ] && continue

    full_name="$nume $prenume"
    summer_data=$(grep "^$full_name" "$SUMMER_FILE")

    if [ -n "$summer_data" ]; then
        media_anuala=$(echo "$summer_data" | awk -v mi="$medie_iarna" '{
            mv = ($3+$4+$5+$6+$7)/5;
            print (mi + mv) / 2
        }')
        echo "$full_name $media_anuala" >> "$TEMP_FILE"
    fi
done < "$INITIAL_FILE"

sort -k3,3nr "$TEMP_FILE" > "$INITIAL_FILE"

rm "$TEMP_FILE"

echo "Succes! Clasamentul anual a fost salvat in '$INITIAL_FILE'."