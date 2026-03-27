#!/bin/bash

users_file="$1"
message_file="$2"

while read user; do
  [ -z "$user" ] && continue
  mail -s "Lab message" "$user" < "$message_file"
done < "$users_file"