#!/bin/bash

W_File="winter_avg.txt"
S_File="summer_avg.txt"
Y_File="yearly_avg.txt"

if [[ ! -f "$W_File" || ! -f "$S_File" ]]; then
  echo "Error! Input files not found."
  exit 1
fi

echo -n "" >temp_res.txt

while read -r name w_avg; do
  s_line=$(grep "^$name " "$S_File")
  if [[ -n "$s_line" ]]; then
    s_avg=$(echo "$s_line" | awk '{print ($2+$3+$4+$5+$6)/5}')
    y_avg=$(awk "BEGIN {print ($w_avg +$s_avg)/2}")
    echo "$name $y_avg" >> temp_res.txt
  fi
done < "$W_File"

sort -k2,2nr temp_res.txt > "$Y_File"
rm temp_res.txt
echo "Update complete! results saved in $Y_File"