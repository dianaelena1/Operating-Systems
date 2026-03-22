#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage: $0 numar1 numar2"
    exit 1
fi

a=$1
b=$2

sum=$((a + b))
diff=$((a - b))
prod=$((a * b))

echo "Sum = $sum"
echo "Difference = $diff"
echo "Product = $prod"