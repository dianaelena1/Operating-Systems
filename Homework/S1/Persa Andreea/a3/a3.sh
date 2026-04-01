#!/bin/bash

month=$1
day=$2

if [ -z "$month" ] || [ -z "$day" ]; then
    echo "Usage: $0 <Month> <Day> (Example: Mar 8)"
    exit 1
fi

echo "Average user connections for $month $day:"

for start_hour in 00 04 08 12 16 20
do
    end_hour=$(printf "%02d" $((10#$start_hour + 4)))
    interval="$start_hour:00-$end_hour:00"

    count=$(cat fake_last.txt | grep "$month" | grep -E " $day | 0$day " | awk -v sh="$start_hour" -v eh="$end_hour" '
        {
            split($8, time, ":")
            hour = time[1]
            if (hour >= sh && hour < eh) {
                sum++
            }
        }
        END { print sum+0 }
    ')

    echo "$interval: $count users"
done