#!/bin/bash

# last - reads the system's log file and prints a list of recent logins, logouts, and system reboots

# grep command works like Ctrl + F in Word

# | grep "$1" takes the output of last and searches it for the first command-line argument ($1). It filters out any lines that do not contain this text
# | grep "$2" takes the remaining lines and filters them again searching for the second command-line argument ($2)
# | grep "$3" takes the lines that passed the first two filters and filters them again based on the third command-line argument ($3)

# | awk ' ' - command designed to extract and manipulate specific pieces of data from within given lines
last | grep "$1" | grep " $2 " | grep "$3" | awk '
    {
        print $1; # extracts and prints the first column of the list (the name of the user) 
        count++; # counts the logs given after we filtered them based on the three arguments 
    }
    END { # END command - it executes once at the end of the execution
        print "Total users:"; # prints the message
        print count; # prints the final value stored in count = the number of total logs given by the arguments
    }'