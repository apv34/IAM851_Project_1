#!/bin/bash

if [ $# != 5 ]; then
  echo "Incorrect number of arguments!"
  exit 1
fi

./convert $1 $2 $3



gnuplot <<- EOF
  reset
  unset key
  j = $5+.2
 set yrange[-.1:j]
  set terminal gif size 1000,800 animate
  set output "$1.gif"
  i = 2
  n = $2
  data = "<paste $4 rotated.txt"
  load "animate.gnuplot"
EOF

