#!/bin/bash

trap `echo "Cokolwiek"` 1 2 3 4 5 6 7 8 9 10

echo PID $$
while true;
  do
    echo $(date +"%H:%M")
    sleep 1
  done
