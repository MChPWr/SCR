#!/bin/bash

trap 'echo "coś robie"' 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

echo MY PID $$
while true;
	do
		echo $(date +"%H:%M")
		sleep 1
done

