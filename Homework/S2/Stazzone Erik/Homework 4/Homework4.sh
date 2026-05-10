#!/bin/bash

LOG_FILE="all_users_activity.log"
declare -A active_sessions

echo "events will be saved to: $LOG_FILE"
echo "Monitoring started press [CTRL+C] to stop."

while read -r user tty; do
    active_sessions["${user}:${tty}"]=1
done < <(who | awk '{print $1, $2}')

while true; do
    unset current_sessions
    declare -A current_sessions

    while read -r user tty; do
        session_key="${user}:${tty}"
        current_sessions["$session_key"]=1

        if [[ -z "${active_sessions[$session_key]}" ]]; then
            timestamp=$(date "+%Y-%m-%d %H:%M:%S")
            log_entry="[$timestamp] CONNECT: User '$user' connected on server/terminal '$tty'"
            echo "$log_entry" | tee -a "$LOG_FILE"
        fi
    done < <(who | awk '{print $1, $2}')

    for session_key in "${!active_sessions[@]}"; do
        if [[ -z "${current_sessions[$session_key]}" ]]; then
            user="${session_key%%:*}"
            tty="${session_key##*:}"
            timestamp=$(date "+%Y-%m-%d %H:%M:%S")
            log_entry="[$timestamp] DISCONNECT: User '$user' disconnected from server/terminal '$tty'"
            echo "$log_entry" | tee -a "$LOG_FILE"
        fi
    done

    unset active_sessions
    declare -A active_sessions
    for key in "${!current_sessions[@]}"; do
        active_sessions["$key"]=1
    done

    sleep 3
done