#!/bin/bash

# $1- first parameter passed, $2 - the second.

# use $(( ... )) for math operations
sum=$(($1 + $2))
difference=$(($1 - $2))
product=$(($1 * $2))

echo "The sum is: $sum"
echo "The difference is: $difference"
echo "The product is: $product"