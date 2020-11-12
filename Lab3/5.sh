#!/bin/bash

trap 'echo "xxx"' 

echo MY PID $$
while true;
	do
		echo $(date +"%H:%M:%S")
		sleep 1
done
