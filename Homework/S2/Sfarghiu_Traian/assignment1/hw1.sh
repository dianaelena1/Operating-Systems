#!/bin/bash

current_month=$(date +"%b")
current_year=$(date +"%Y")
LOGIN_FILE="logins.txt"

while true; do
    read -p "Enter a username (or 'stop' to quit): " username
    if [ "$username" = "stop" ]; then
        break
    fi

    count=$(grep -E "^$username[[:space:]]" "$LOGIN_FILE" | grep " $current_month " | wc -l)

    if [ "$count" -eq 0 ]; then
        echo "User $username has never logged in during the current month."
    else
        echo "User $username has logged in $count time(s) during the current month."
    fi
done
