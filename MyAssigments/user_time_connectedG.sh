#!/bin/bash

# check for exactly two arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <Month> <Day>"
    exit 1
fi

MONTH=$1
DAY=$2

echo "Searching logins for: $MONTH $DAY"
echo "------------------------------"

# $1 is Month (Mar), $2 is Day (21)
# Using ($6 + 0) ensures " 8" and "8" both work.
# Using 'sort -u' ensures we don't list the same user twice.

last | awk -v m="$1" -v d="$2" '$5 == m && ($6 + 0) == d {print $1}' | sort -u