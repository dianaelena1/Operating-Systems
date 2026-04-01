#!/bin/bash

user=$1
file=$2

for u in $(cat $user)
do
    mail -s "hello world" $u < $file
    echo "Sent mail to $u"
done