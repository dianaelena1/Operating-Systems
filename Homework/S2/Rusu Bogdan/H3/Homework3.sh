#!/bin/bash

# last - reads the system's log file and prints a list of recent logins, logouts, and system reboots

# grep command works like Ctrl + F in Word
last | grep "$1" | grep " $2 " | grep "$3" | awk '
    {
        print $1; # extracts and prints the first column of the list (the name of the user) 
        count++; # counts the logs given after we filtered them based on the three arguments 
    }
    END { # END command - it executes once at the end of the execution
        print "Total users:"; # prints the message
        print count; # prints the final value stored in count = the number of total logs given by the arguments
    }'