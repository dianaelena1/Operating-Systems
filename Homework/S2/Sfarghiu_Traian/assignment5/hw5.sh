#!/bin/bash

for file in "$@"; do
    if [ -f "$file" ]; then
        result=$(awk '
        BEGIN { 
            sum = 0; 
            l1 = 0; 
            l2 = 0 
        }
        {
            # Check if the current line matches the regular expression for a digit [0-9]
            if (/[0-9]/) {
                l1++
            } else {
                l2++
            }
            
            # Replace all non-digit characters with a space
            gsub(/[^0-9]+/, " ")
            
            # Loop through the remaining fields (which are now only numbers) and add to sum
            for (i = 1; i <= NF; i++) {
                sum += $i
            }
        }
        # The END block executes once only, AFTER all the input is read
        END {
            # Print the calculated values
            print "sum = " sum+0 " l1/l2 = " l1+0 "/" l2+0
        }' "$file")

        echo "$file $result"
    else
        echo "$file: File not found or is not a regular file."
    fi
done
