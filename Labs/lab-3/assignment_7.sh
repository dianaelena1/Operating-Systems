#!/usr/bin/env bash
# ============================================================
#  Takes a directory name as parameter and determines the
#  total number of lines in all ASCII text files in that
#  directory and its subdirectories.
# ============================================================

set -euo pipefail

# ----------------------------
# Check that exactly one argument was provided
# ----------------------------
if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

dir="$1"

# ----------------------------
# Check that the argument is a valid directory
# ----------------------------
if [[ ! -d "$dir" ]]; then
    echo "Error: '$dir' is not a valid directory."
    exit 1
fi

# ----------------------------
# Count total lines across all ASCII text files
# ----------------------------
total_lines=0

# find recursively searches for regular files (-type f)
while IFS= read -r -d '' filepath; do
    filetype="$(file --brief "$filepath")"
    if [[ "$filetype" == *"ASCII text"* ]]; then
        lines=$(wc -l < "$filepath")
        total_lines=$(( total_lines + lines ))
        echo "  $filepath: $lines line(s)"
    fi
done < <(find "$dir" -type f -print0)

echo "Total lines in all ASCII text files: $total_lines"