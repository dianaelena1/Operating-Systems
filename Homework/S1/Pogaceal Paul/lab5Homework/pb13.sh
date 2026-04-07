#!/bin/bash

# split the 3rd parameter (18.40-18.45) and replace dots with colons
IFS='-' read t1 t2 <<< "${3//./:}"

# 'last' output, match the date, and check if times overlap
last | awk -v m="$1" -v d="$2" -v t1="$t1" -v t2="$t2" '
$0 ~ m " +" d {                                  # match the m and d
    if ($1 == "reboot" || $1 == "wtmpdb") next;  # skip system boot entries

    for(i=1; i<=NF; i++) {                       # NF = number of fields
        if($i == "-") {                          # "-" => locate times
            login = $(i-1)
            logout = $(i+1)
            
            # string comparison for 24h time format overlap
            if (login <= t2 && (logout >= t1 || logout == "still")) {
                users[$1] = 1                    # unique username, on the 1st column
            }
        }
    }
}
END {
    for (u in users) { 
        print u
        count++ 
    }
    print "Total users: " count+0
}'