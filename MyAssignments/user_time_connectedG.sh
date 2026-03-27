#!/bin/bash

# 1. check if exactly two arguments are provided (Month and Day)
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <Month> <Day>"
    echo "Example: $0 Mar 8"
    exit 1
fi

MONTH=$1
DAY=$2

# 2. handle the spacing issue in the 'last' command output.
# The 'last' command prints single-digit days with an extra leading space.
# Example: "Mar  8" (two spaces) vs "Mar 21" (one space).
if [ ${#DAY} -eq 1 ]; then
    # day is 1 digit (1-9) -> we use two spaces
    SEARCH_PATTERN="$MONTH  $DAY"
else
    # day is 2 digits (10-31) -> we use one space
    SEARCH_PATTERN="$MONTH $DAY"
fi

echo "Searching logins for: $SEARCH_PATTERN"
echo "------------------------------"

# 3. pipeline
# - last: Gets the system login history.
# - grep "$SEARCH_PATTERN": Filters lines matching the specific date.
# - cut -d' ' -f1: Extracts only the first column (the username).
# - grep -v -e "reboot" -e "wtmp": Excludes system entries that aren't real users.
# - sort -u: Sorts the list and removes duplicate names.

last | grep "$SEARCH_PATTERN" | cut -d' ' -f1 | grep -v -e "reboot" -e "wtmp" | sort -u