#!/bin/bash
echo "Introdu numele utilizatorului:"
read username

nr_logari=$(last $username | grep $username | wc -l)

if [ $nr_logari -gt 0 ]; then
    echo "Utilizatorul $username s-a logat de $nr_logari ori în această lună."
else
    echo "User $username has never logged in during the current month"
fi