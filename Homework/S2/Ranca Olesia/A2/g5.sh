#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 command_name"
    exit 1
fi

cmd="$1"

ps aux | grep "$cmd" | grep -v grep | awk '{print $1}' | sort | uniq
