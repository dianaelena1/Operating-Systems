#!/bin/bash


if [ $# -eq 0 ]; then
    echo "Use: $0 [file1] [file2] etc"
    exit 1
fi

file=$1
error="Error"


if [ ! -f "$file" ]; then
    echo "$error :file not found"
    exit 1
fi

echo "Monitoring"


while true; do

    if ps aux | grep "ftp" | grep -v "grep" > /dev/null; then
        
        now=$(date)
        

        echo "Connection Attempt at $now" >> "$file"
        ps aux | grep "ftp" | grep -v "grep" >> "$file"
        echo "" >> "$file"
        
    fi

    sleep 5
done

