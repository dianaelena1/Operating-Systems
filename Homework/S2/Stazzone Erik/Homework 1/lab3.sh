#!/bin/bash

input_file="who_output.txt"

echo "full name|IP address"

while read -r line; do
    user=$(echo "$line" | awk '{print $1}')

    ip=$(echo "$line" | grep -o '([^)]*)' | sed 's/[()]//g')

    if [ -z "$ip" ]; then
        ip="Local"
    fi

    fullname=$(getent passwd "$user" | cut -d: -f5 | cut -d, -f1)


    [ -z "$fullname" ] && fullname="$user"

    printf "%-20s %-20s\n" "$fullname" "$ip"
done < "$input_file"


