#!/bin/bash

if [-z "$1"]; then
  echo "Usage: $0 <username>"
  exit 1
fi

USER_NAME=$1

if !id "$USER_NAME" >/dev/null 2>$1; then
  echo "Error: User '$USER_NAME' does not exist."
  exit 1
fi

COUNT=$(ps -u "$USER_NAME" --no-headers | wc -l)

echo "User '$USER_NAME' is currently running $COUNT process(es)"