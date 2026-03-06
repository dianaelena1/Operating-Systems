#!/bin/bash

# In bash scripts, $1 is the first parameter passed, and $2 is the second.

# Calculate the results using $(( ... )) for math operations
sum=$(($1 + $2))
difference=$(($1 - $2))
product=$(($1 * $2))

# Display the results
echo "The sum is: $sum"
echo "The difference is: $difference"
echo "The product is: $product"