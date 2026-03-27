#!/bin/bash
#test
num=$1

# Basic validation
if [[ ! $num =~ ^[0-9]+$ ]] || [ "$num" -lt 1 ]; then
    echo "Please enter a valid natural number."
    exit 1
fi

if [ "$num" -eq 1 ]; then
    echo "1 is not a prime number."
    exit 0
fi

# We check factors starting from 2
for (( i=2; i*i<=$num; i++ ))
do
    if [ $((num % i)) -eq 0 ]; then
        echo "$num is not a prime number."
        exit 0
    fi
done

echo "$num is a prime number."