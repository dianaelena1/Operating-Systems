#!/bin/bash

group_name=$1

if [ -z "$group_name" ]; then
    echo "Usage: $0 <group_name>"
    exit 1
fi

members=$(grep "^${group_name}:" test_groups.txt | cut -d: -f4)

if [ -z "$members" ]; then
    echo "Group '$group_name' not found or has no members."
else
    echo "Group: $group_name"
    echo "Members: $members" | tr ',' '\n'
fi