#!/bin/bash

sum=0

while true
do
    read -p "Enter a number (0 to stop): " num

    if test "$num" -eq 0; then
        break
    fi

    sum=$((sum + num))
done

echo "The sum of the numbers is: $sum"