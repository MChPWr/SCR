#!/bin/sh

trap '""' 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
while true;
do
	echo echo;
	sleep 1;
done

# zgodnie z tym co w instrukcji, w tym momencie nie mozna zamknac procesu tymi czterema sygnalami tj. SIGINT, SIGILL SIGQUIT, SIGFPE.

# SIGKILL zabije proces mimo przechwytywanie 15 podstawowych sygnalow
