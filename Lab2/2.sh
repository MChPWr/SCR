#!/bin/bash

while read email;
do
	echo "" | mutt -s "SCR - zadanie 2" -i tresc.txt -a spec*.pdf -- $email;
done < adresy.txt
