#!/usr/bin/env bash
# ============================================================
#  bash_script.sh — Bash Scripting Basics (demo for students)
# ============================================================

set -euo pipefail

# ----------------------------
# 1) Variables + User Input
# ----------------------------
username="Jay"
filename="${3:-}"   # third CLI argument (or empty if not provided)

read -r -p "Enter your username: " user
echo "Username: $user"

# ----------------------------
# 2) If statement (check user)
# ----------------------------
if [[ "${EUID}" -ne 0 ]]; then
  echo "You are not running this script as the root user."
else
  echo "You are running this script as the root user."
fi

# ----------------------------
# 3) For loop
# ----------------------------
echo "Counting to 5:"
for i in {1..5}; do
  echo "$i"
done

# ----------------------------
# 4) Functions
# ----------------------------
greet() {
  echo "Hello, $1!"
}
greet "Alice"

# ----------------------------
# 5) Case statement
# ----------------------------
echo "Enter a number between 1 and 2:"
read -r num
case "$num" in
  1) echo "You chose one." ;;
  2) echo "You chose two." ;;
  *) echo "Invalid choice." ;;
esac

# ----------------------------
# 6) File operations (exists + is directory)
#    Uses the 3rd argument as filename/path
# ----------------------------
if [[ -n "$filename" ]]; then
  if [[ -e "$filename" && -d "$filename" ]]; then
    echo "File exists and is a directory."
  else
    echo "File does not exist or is not a directory."
  fi
else
  echo "Tip: pass a 3rd argument to test file/dir checks (example below)."
fi

# ----------------------------
# 7) Command line arguments
# ----------------------------
echo "First argument: ${1:-<missing>}"
echo "Second argument: ${2:-<missing>}"

# ----------------------------
# 8) Exit status codes + stderr redirection
# ----------------------------
cat nonexistent-file.txt 2>/dev/null || true
echo "Exit status: $?"

# ----------------------------
# 9) Indexed arrays
# ----------------------------
fruits=("Apple" "Orange" "Banana")
echo "Fruits: ${fruits[0]}"

# ----------------------------
# 10) Associative arrays
# ----------------------------
declare -A capitals
capitals[USA]="Washington D.C."
capitals[France]="Paris"
echo "Capital of France: ${capitals[France]}"

# ----------------------------
# 11) Command substitution
# ----------------------------
current_date="$(date)"
echo "Today's date is: $current_date"

# ----------------------------
# 12) Command redirection
# ----------------------------
echo "This is a sample text." > example.txt
find / -name hello.txt &>/dev/null || true

# ----------------------------
# 13) Arithmetic operations
# ----------------------------
result=$((15 - 2))
echo "$result"

# ----------------------------
# 14) Parameter expansion
# ----------------------------
SRC="/path/to/foo.cpp"
BASEPATH="${SRC%/*}"
echo "$BASEPATH"

# ----------------------------
# 15) Process signal handling (trap)
# ----------------------------
trap 'echo "Received SIGTERM signal. Cleaning up..."; exit' SIGTERM

# ----------------------------
# 16) Comments
# ----------------------------
# This is a single line comment

: '
This is a multiline comment
(works as a no-op string block)
'

# Keep the script alive briefly so SIGTERM can be tested in class (optional)
# sleep 10