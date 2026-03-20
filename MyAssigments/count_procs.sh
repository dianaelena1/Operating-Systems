#!/bin/bash

# check if username given
if [ -z "$1" ]; then
    echo "Usage: $0 <username>"
    exit 1
fi

USER_NAME=$1

# -u filters by user name
# --no-headers removes the column titles (so they aren't counted)
COUNT=$(ps -u "$USER_NAME" --no-headers | wc -l)

# results
echo "User '$USER_NAME' is currently running $COUNT processes."
