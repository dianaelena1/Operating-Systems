#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

GROUP_NAME=$1

group_id=$(getent group "$GROUP_NAME" | cut -d: -f3)

if [ -z "$group_id" ]; then
    echo "'$GROUP_NAME' doesnt exist"
    exit 1
fi

echo "'$GROUP_NAME'"

awk -F: -v target_gid="$group_id" '
    $4 == target_gid {
        split($5, name, ",")
        print $1, name[1]
    }
' /etc/passwd