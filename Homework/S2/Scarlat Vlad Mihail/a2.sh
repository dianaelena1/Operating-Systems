nano convert.sh

  #!/bin/sh

  if [ $# -eq 0 ]; then
      echo "Usage: $0 file.html"
  else
      sed 's/<[^>]*>//g' "$1" > text.txt
      echo "Converted to .txt"
  fi

facem sa putem apela cu   chmod +x convert.sh
cream un html file   nano page.html

  <html>
  <head><title>Test</title></head>
  <body>
  <h1>Haudi</h1>
  <p>Calul face tagadamtagadamtagadam</p>
  </body>
  </html>

./convert.sh page.html

cat text.txt