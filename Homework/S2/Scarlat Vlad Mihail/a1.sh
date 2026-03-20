#!/bin/bash

who | while read username terminal date time host
do
    full_name=$(cat /etc/passwd | grep "^$username:" | cut -d: -f5 | cut -d, -f1)
    #gigi:password:1000:1000:Gigi Becali,,,:/home/gigi:/bin/bash
    # f1  f2  f3  f4      f5
    if [[ -z "$full_name" ]]; then
        full_name="$username"
    fi

    if [[ -z "$host" ]]; then
        ip="local"
    else
        ip=$(echo "$host" | cut -d'(' -f2 | cut -d')' -f1)
        #(-d'(' f2 splits here ->192.168.1.10 <-same for ...f1)
    fi

    echo "User: $full_name | IP: $ip"
done