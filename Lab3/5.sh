#!/bin/bash

trap 'echo "coś robie"' 1 2 3 4 5 6 7 8 9 10

echo MY PID $$
while true;
	do
		echo $(date +"%H:%M:%S")
		sleep 1
done

