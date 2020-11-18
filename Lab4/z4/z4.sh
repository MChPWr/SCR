#!/bin/bash

a=1;
trap "echo trap" {1..15}

while [ $a -le 10000 ] ; do
	a=$[a+1]
echo "PID:  $$  "
	sleep 1s
done