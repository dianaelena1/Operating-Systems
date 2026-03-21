#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Error: Please provide a username as a parameter."
    echo "Usage: $0 <username>"
    exit 1
fi

USERNAME=$1

if ! id "$USERNAME" &>/dev/null; then
    echo "Error: User '$USERNAME' does not exist."
    exit 1
fi

PROCESS_COUNT=$(ps -u "$USERNAME" --no-headers | wc -l)

echo "The user '$USERNAME' is running $PROCESS_COUNT processes."