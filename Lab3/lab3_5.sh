#!/bin/sh

#print time every second
trap '""' HUP INT FPE ILL 
while true;
do
	echo echo;
	sleep 1;
done

# zgodnie z tym co w instrukcji, w tym momencie nie mozna zamknac procesu tymi czterema sygnalami
# o co chodzi z tymi 15 podstawowymi?