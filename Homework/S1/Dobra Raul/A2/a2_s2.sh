#s2	Write a shell script which takes as parameters a text followed by several file names. The script will delete all the lines which contain the text given as parameter in all given files.
#!/bin/bash

if [ $# -lt 2 ]; then
    echo "Utilizare: $0 <text_cautat> <fisier1> <fisier2> ..."
    exit 1
fi

TEXT_CAUTAT=$1

shift

for FISIER in "$@"; do

    if [ -f "$FISIER" ]; then
        echo "Se procesează fișierul: $FISIER"./script.sh "cuvant_interzis" fisier1.txt fisier2.txt
        sed -i "/$TEXT_CAUTAT/d" "$FISIER"
    else
        echo "Eroare: Fișierul $FISIER nu a fost găsit."
    fi
done

echo "Operațiune finalizată."