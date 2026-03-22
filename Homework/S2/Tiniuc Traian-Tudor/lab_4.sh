#!/bin/bash

# ------------------------------------------------------------
# Check that exactly one argument was provided
# ------------------------------------------------------------
if [[ $# -ne 1 ]]; then
    echo "Usage: $0 <command_name>"
    exit 1
fi

command_name="$1"

# ------------------------------------------------------------
# Check if the command exists on the system
# ------------------------------------------------------------
if ! command -v "$command_name" &> /dev/null; then
    echo "Error: Command '$command_name' not found on this system."
    exit 1
fi

# ------------------------------------------------------------
# Display all user accounts running the command
# ------------------------------------------------------------
echo "Users running the command '$command_name':"


ps aux | grep "$command_name" | grep -v "grep" | awk '{print $1}' | sort | uniq