echo "1. Directory content sorted by NAME"
ls -lv --group-directories-first
echo "2. Directory content sorted by DATE (Newest first)"
ls -lt
echo "3. Directory content sorted by SIZE (Largest first)"
ls -lS
for file in *; do
    if [ -f "$file" ] && [ "$file" != "list_supplies.sh" ]; then
        if file "$file" | grep -iq "text"; then
            echo "--- Item: $file ---"
            head -n 3 "$file"
            echo ""
        fi
    fi
done
