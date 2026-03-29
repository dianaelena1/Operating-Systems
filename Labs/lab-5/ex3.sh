#!/bin/bash

file=$1

lines=$(wc -l < "$file")
words=$(wc -w < "$file")
chars=$(wc -c < "$file")

echo "Lines: $lines"
echo "Words: $words"
echo "Characters: $chars"