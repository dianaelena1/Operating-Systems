#!/bin/bash

# Write a shell script which takes as parameter a group name (ex: gr821).
# The script will display the given group name followed by the list of all users that belongs to that group.

if [ -z "$1" ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

GROUP_NAME=$1

GROUP_ENTRY=$(grep "^${GROUP_NAME}:" /etc/group)

if [ -z "$GROUP_ENTRY" ]; then
    echo "Error: Group '$GROUP_NAME' does not exist."
    exit 1
fi

USERS=$(echo "$GROUP_ENTRY" | cut -d: -f4)

echo "Group: $GROUP_NAME"
if [ -z "$USERS" ]; then
    echo "Users: (No users explicitly assigned to this group)"
else
    echo "Users: ${USERS//,/ }"
fi