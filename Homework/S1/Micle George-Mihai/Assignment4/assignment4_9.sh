#!/bin/bash

SERVER=$(hostname)

if [ $# -eq 0 ]; then
    echo "Please provide usernames."
    exit 1
fi

echo "Monitoring terminal sessions for: $@"

while true; do
    for user in "$@"; do
        current=$(ps -u "$user" 2>/dev/null | grep -c -w "bash")
        
        if [ ! -f "$user.txt" ]; then
            echo "$current" > "$user.txt"
        fi
        
        previous=$(cat "$user.txt")
        
        if [ "$current" -gt "$previous" ]; then
            echo "$user | $(date) | Terminal Opened | $SERVER" >> system.log
            echo "-> Activity logged for $user (Opened)" 
        fi
        
        if [ "$current" -lt "$previous" ]; then
            echo "$user | $(date) | Terminal Closed | $SERVER" >> system.log
            echo "-> Activity logged for $user (Closed)" 
        fi
        
        echo "$current" > "$user.txt"
        
    done

    sleep 5
done