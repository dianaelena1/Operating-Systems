#!/bin/bash

LOG_FILE="ftp_supervision.log"

echo "Monitoring started. Logging to $LOG_FILE..."

while true; do
    # find ftp processes
    pgrep -f "ftp" | while read -r PID; do
        
        # get user, start time, command
        USER_INFO=$(ps -p "$PID" -o user=,lstart=,args=)
        
        # avoid logging same PID again
        if ! grep -q "PID:$PID" "$LOG_FILE" 2>/dev/null; then
            
            # extract user and server
            USER=$(echo "$USER_INFO" | awk '{print $1}')
            SERVER=$(echo "$USER_INFO" | awk '{print $NF}')
            
            # if only 'ftp', no server yet
            if [ "$SERVER" == "ftp" ]; then
                SERVER="No server specified yet"
            fi

            TIMESTAMP=$(date "+%Y-%m-%d %H:%M:%S")
            
            # log result
            echo "[$TIMESTAMP] User: $USER | Server: $SERVER | PID:$PID" >> "$LOG_FILE"
        fi
    done
    
    # wait a bit
    sleep 2
done