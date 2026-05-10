#!/bin/bash

if [ -z "$1" ]; then # checks if the first command-line argument "$1" is an empty string (-z)
    echo "Please provide one argument" # if there is no argument, the program gives this prompt
    exit 1 # and stops the script from running
fi

if [ ! -d "$1" ]; then # checks if the provided argument is NOT a directory
    echo "Argument must be a directory" # if the argument is not a directory, the program gives this prompt
    exit 1 # and stops the script from running
fi


find "$1" | awk -F/ '{print $NF}' | sort | uniq -c