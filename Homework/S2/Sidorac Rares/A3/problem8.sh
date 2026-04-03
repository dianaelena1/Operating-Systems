#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Use: $0 [file1] [file2] etc"
    exit 1
fi

for file in "$@"; do
    [ ! -f "$file" ] && echo "$error :file not found" && continue
    awk '
    {
        sum_line = 0
        has_num = 0
        for (i = 1; i <= NF; i++) {
            if ($i + 0 == $i && $i ~ /^-?[0-9]+\.?[0-9]*$/) {
                sum_line += $i
                has_num = 1
            }
        }
        if (has_num) {
            total += sum_line
            with++
        } else {
            without++
        }
    }
    END {
        printf "%s sum = %d | %d:%d", FILENAME, total, with, without
        if (with + without > 0 && without > 0) {
            printf " = %.2f\n", with/without
        } else {
            print ""
        }
    }' "$file"
done
