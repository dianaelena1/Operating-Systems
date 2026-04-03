#!/bin/bash

# Write a shell script which takes as parameters two words followed by several file names.
# The script will replace any occurrence of the first word with the second word in each line of the given files.

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 <search> <replace> [files...]"
    exit 1
fi

oldWord=$1
newWord=$2
shift 2

if [ "$#" -gt 0 ]; then
    for file in "$@"; do
        if [ -f "$file" ]; then
            awk -v old="$oldWord" -v new="$newWord" '{
                result = ""
                len = length($0)
                i = 1
                while (i <= len) {
                    found = 0
                    if (i <= len - length(old) + 1) {
                        if (substr($0, i, length(old)) == old) {
                            result = result new
                            i += length(old)
                            found = 1
                        }
                    }
                    if (!found) {
                        result = result substr($0, i, 1)
                        i++
                    }
                }
                print result
            }' "$file" > "$file.tmp" && mv "$file.tmp" "$file"
        else
            echo "Skipping '$file': Not a valid file."
        fi
    done
else
    awk -v old="$oldWord" -v new="$newWord" '{
                result = ""
                len = length($0)
                i = 1
                while (i <= len) {
                    found = 0
                    if (i <= len - length(old) + 1) {
                        if (substr($0, i, length(old)) == old) {
                            result = result new
                            i += length(old)
                            found = 1
                        }
                    }
                    if (!found) {
                        result = result substr($0, i, 1)
                        i++
                    }
                }
                print result
            }'
fi