#!/bin/bash

if [ $# -eq 0 ]; then
  echo "Usage: $0 user1 [user2 ...]"
  exit 1
fi

echo "Currently connected users from your list:"

for user in "$@"; do
  if who | grep -q "^$user\b"; then
    echo "$user is connected"
  else
    echo "$user is not connected"
  fi
done