#!/bin/sh
export LC_ALL=C

DATE=`date`; 
#echo "Dziś jest: ${DATE}"
set `date`

DAY=$1

if [ ${DAY} = 'sat,' ] || [ ${DAY} = 'sun,' ]
then
	echo "Mamy weekend. Pora odpocząć!"
else
	echo "Mamy dzień roboczy. Obowiązki czekają!"
fi
exit