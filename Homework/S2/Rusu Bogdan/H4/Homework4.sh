#!/bin/bash

if [ -z "$1" ]; then # checks if the first command-line argument "$1" is an empty string (-z)
    echo "Please provide one argument" # if there is no argument, the program gives this prompt
    exit 1 # and stops the script from running
fi

if [ ! -d "$1" ]; then # checks if the provided argument is NOT a directory
    echo "Argument must be a directory" # if the argument is not a directory, the program gives this prompt
    exit 1 # and stops the script from running
fi

# 1. find "$1" - lists all files and directories starting from the directory passed as the first parameter
# 2. awk -F/ '{print $NF}' - uses awk to change the field separator to a slash (/), and prints the last field ($NF) of each line to isolate the base file or directory from its full path
# 3. sort - alphabetically sorts the list of names so identical names are placed adjacent to one another
# 4. uniq -c - collapses adjacent identical lines into a single line, prefixing it with the count of how many times it appeared (-c)
find "$1" | awk -F/ '{print $NF}' | sort | uniq -c