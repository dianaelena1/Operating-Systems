#!/bin/bash

echo "Enter your name:"
read name

echo "Enter your age:"
read age


echo "Hello $name! I am $age years old!"

if [ "$age" -ge 18 ]; then
	echo "You are an adult"
else
	echo "You are a minor"
fi
