#!/bin/bash

dir="$1"

if [ ! -d "$dir" ]; then
	echo "Usage: $0 directory"
	exit 1
fi

for file in "$dir"/*
do
	if [ -f "$file" ]; then
		if file "$file" | grep -q "ASCII text"; then
			echo "Filename: $(basename "$file")"
			head -n 3 "$file"
			echo
		fi
	fi
done
