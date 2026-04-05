#!/bin/bash

for host in "$@"
do
    ping -c 1 "$host" 1> /dev/null 2> /dev/null

    if [ "$?" -eq 0 ]; then
        echo "$host is alive"
    fi
done