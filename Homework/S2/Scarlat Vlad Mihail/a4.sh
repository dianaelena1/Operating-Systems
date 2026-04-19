#!/bin/sh

month=$1
day=$2

for start in 0 4 8 12 16 20
do
    end=$((start+4))
    avg=$(last | awk -v m="$month" -v d="$day" -v s="$start" -v e="$end" '
    $5==m && $6==d {
        split($7,t,":")
        h=t[1]
        if(h>=s && h<e) c++
    }
    END{
        print c/4
    }')
    printf "%02d:00-%02d:00 %.2f\n" "$start" "$end" "$avg"
done