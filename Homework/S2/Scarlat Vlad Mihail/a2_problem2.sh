#!/bin/sh

if [ $# -eq 0 ]; then
    echo "Usage: $0 user1 user2 ..."
else
    for user in "$@"
    do
        count=$(cat last.txt | grep "^$user " | wc -l)

        if [ "$count" -eq 0 ]; then
            echo "$user"
        fi
    done
fi