#!/bin/bash
#Problema 7
# Verificăm dacă am primit folderul ca argument
if [ -z "$1" ] || [ ! -d "$1" ]; then
    echo "Eroare: introdu un nume de director valid."
    exit 1
fi

# Găsim toate fișierele și le trimitem la 'wc' pentru numărare
total=$(find "$1" -type f -exec cat {} + | wc -l)

echo "Numărul total de linii este: $total"
