#!/bin/bash
read -p "Enter your name: " name
read -p "Enter your age: " age

echo "Hello $name! I am $age years old."

if [ $age -ge 18 ]; then
    echo "You are an adult."
else
    echo "You are a minor."
fi