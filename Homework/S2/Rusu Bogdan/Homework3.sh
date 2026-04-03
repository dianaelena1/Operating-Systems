#!/bin/bash

last | grep "$1" | grep " $2 " | grep "$3" | awk '
    {
        print $1;
        count++;
    }
    END {
        print "Total users:";
        print count;
    }'