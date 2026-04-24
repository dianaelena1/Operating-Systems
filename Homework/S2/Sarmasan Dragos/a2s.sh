#!/bin/bash

# check at least one argument is provided
if [ $# -eq 0 ]; then
    exit 1
fi

logged_in=$(who | awk '{print $1}')

for user in "$@"; do
    who | grep -w "$user" && echo "$user connected"
done

