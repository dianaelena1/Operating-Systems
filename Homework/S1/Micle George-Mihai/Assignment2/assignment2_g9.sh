#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Error: Please provide at least one username as a parameter."
    echo "Usage: $0 <username1> <username2> ..."
    exit 1
fi

for user in "$@"; do
    if who | grep -wq "^$user"; then 
        echo "$user is currently connected to the server."
    else
        echo "$user is not connected."
    fi
done