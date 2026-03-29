#!/bin/bash

echo "For Loop"
for i in $(seq 1 10); do
    echo $i
done

echo "While Loop"
i=1
while [ $i -le 10 ]; do
    echo $i
    ((i++))
done

echo "Until Loop"
i=1
until [ $i -gt 10 ]; do
    echo $i
    ((i++))
done