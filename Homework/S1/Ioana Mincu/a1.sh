#!/bin/bash

echo "Searching for group-writable files in: $(pwd)"
find . -type f -perm -g+w
