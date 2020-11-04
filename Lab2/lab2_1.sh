#!/bin/bash

#website with all date formates in bash: 
#https://www.shell-tips.com/linux/how-to-format-date-and-time-in-linux-macos-and-bash/

clear 

LC_ALL=C
dayNumber=$(date +%u) # var which value is day of the week
					  # where 1 is Mon, 2 is Tue etc.

if [ $dayNumber -gt 5 ]; then # if day value is greater than 5
							  # -lt means the opposite - less than
	echo "Weekend"
else
	echo "One day from a days between Mon-Fri"
fi 

fullDate=$(date)
#echo $fullDate

if [[ $fullDate = *"20 Oct"* ]]; then # check if the returned
									  # string contains substring  
									  # have to remember about double brackets
	echo "OK, it's 20 Oct"
else 
	echo "See you in the next year :("
fi

