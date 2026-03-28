#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

GROUP_NAME=$1

# get the GID and the list of secondary members from /etc/group
# $3 is GID, $4 is the comma-separated list of users
read -r GID SECONDARY_USERS < <(awk -F: -v g="$GROUP_NAME" '$1 == g {print $3, $4}' /etc/group)

if [ -z "$GID" ]; then
    echo "Error: Group '$GROUP_NAME' does not exist."
    exit 1
fi

echo "Group: $GROUP_NAME (GID: $GID)"
echo "---------------------------"

# use awk to find users who have this GID as primary 
# OR whose name appears in the secondary list
awk -F: -v target_gid="$GID" -v secondary="$SECONDARY_USERS" '
    BEGIN {
        split(secondary, sec_array, ",")
        for (i in sec_array) sec_map[sec_array[i]] = 1
    }
    $4 == target_gid || sec_map[$1] == 1 {
        # This line removes the commas and everything after them
        sub(/,.*/, "", $5) 
        print $1, $5
    }
' /etc/passwd