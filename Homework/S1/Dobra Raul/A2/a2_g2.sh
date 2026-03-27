#s2	Write a shell script which takes as parameters a text followed by several file names. The script will delete all the lines which contain the text given as parameter in all given files.
#!/bin/bash


if [ $# -lt 2 ]; then
    echo "Utilizare: $0 <cuvant> <fisier1> <fisier2> ..."
    exit 1
fi

CUVANT=$1

shift

TOTAL_FISIERE=0

echo "Fișierele care conțin cuvântul '$CUVANT' sunt:"
echo "----"


for FISIER in "$@"; do

    if [ -f "$FISIER" ]; then
        if grep -q "$CUVANT" "$FISIER"; then
            echo "- $FISIER"
            TOTAL_FISIERE=$((TOTAL_FISIERE + 1))
        fi
    else
        echo "Eroare: $FISIER nu a fost găsit."
    fi
done

echo "----"
echo "Total fișiere găsite: $TOTAL_FISIERE"