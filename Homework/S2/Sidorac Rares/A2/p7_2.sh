#!/bin/bash

if [ $# -eq 0 ]; then
    echo "use: $0 [hostname1] [hostname2] ..."
    exit 1
fi



#for host in "$@"; do
#     if ping -c 1 -W 2 "$host" > /dev/null; then
#        echo "$host"
#    fi
#done


for host in "$@"; do
    ping -c 1 -W 2 "$host" 2>&1 | grep -q "1 received" && echo "$host"
done