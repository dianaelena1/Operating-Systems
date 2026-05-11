#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Error: Provide a short month name and a day (e.g., ./connection_history.sh Mar 8)"
    exit 1
fi

MONTH=$1
DAY=$2

echo "--- User accounts connected on $MONTH $DAY ---"

last | grep -E "$MONTH +$DAY" | awk '{print $1}' | sort -u