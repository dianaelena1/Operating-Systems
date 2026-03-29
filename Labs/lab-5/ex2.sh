#!/bin/bash
read -p "Enter first number: " a
read -p "Enter second number: " b

echo "Sum: $((a + b))"
echo "Difference: $((a - b))"
echo "Product: $((a * b))"
echo "Division: $((a / b))"
echo "Modulo: $((a % b))"