#!/bin/bash

# Problem 2:
# Write a shell script which takes as parameters two names of text files.
# The script will compare the two text files line by line and display the first 3 text lines that differ.

# How I ran this script:
# 1. Go into file
# 2. Make file executable: chmod +x Assignment1.sh
# 3. Run executable file: ./Assignment1.sh [file1] [file2]

# Check if exactly two arguments are provided
if [ "$#" -ne 2 ]; then
  # Print correct format
    echo "Usage: $0 file1.txt file2.txt"
    exit 1
fi

# Assigning our arguments to some variables.
file1=$1
file2=$2

# Check if both files exist. Error is displayed in case one or both files do not exist.
if [[ ! -f "$file1" || ! -f "$file2" ]]; then
    echo "Error: One or both files do not exist."
    exit 1
fi

# Initialize a counter to spot differences.
count=0

# Open both files using file descriptors 3 and 4
exec 3< "$file1"
exec 4< "$file2"

# Loop that checks for differences at each line
while [ $count -lt 3 ]; do
    # Read one line from each file descriptor into a local variable.
    # Then we capture the exit status for their respective read commands.
    read -r line1 <&3
    res1=$?
    read -r line2 <&4
    res2=$?

    # If both files ended, break the loop
    if [[ $res1 -ne 0 && $res2 -ne 0 ]]; then
        break
    fi

    # Compare the lines
    if [[ "$line1" != "$line2" ]]; then
        ((count++))
        echo "Difference at line #$count: "
        echo "File 1: ${line1:-(empty/EOF)}"
        echo "File 2: ${line2:-(empty/EOF)}"
        # Blank line
        echo ""
    fi
done

# Close the file descriptors
exec 3<&-
exec 4<&-

if [ $count -eq 0 ]; then
    echo "No differences found."
fi