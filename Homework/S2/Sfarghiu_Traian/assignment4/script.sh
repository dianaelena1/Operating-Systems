#!/bin/bash

while true; do
    echo "Connection Monitoring" 
    
    users=$(who | awk '{print $1}' | sort | uniq)
    
    for user in $users; do
        proc_count=$(ps -u "$user" | grep -v "PID" | wc -l)
        echo "User: $user | Active Processes: $proc_count"
    done
    
    sleep 5
done
