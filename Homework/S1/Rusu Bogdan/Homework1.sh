#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <group_number>"
    exit 1
fi

TARGET_GROUP="$1"
GROUP_ENTRY=$(getent group "$TARGET_GROUP")

if [ -z "$GROUP_ENTRY" ]; then
    echo "Error: Group '$TARGET_GROUP' does not exist."
    exit 2
fi

GID=$(echo "$GROUP_ENTRY" | cut -d: -f3)

printf "%-15s | %-30s | %s\n" "Username" "Full Name" "Home Directory"
printf "%s\n" "------------------------------------------------------------------------"

getent passwd | awk -F: -v target_gid="$GID" '$4 == target_gid {
    split($5, gecos_parts, ",")
    full_name = gecos_parts[1]
    printf "%-15s | %-30s | %s\n", $1, full_name, $6
}'
