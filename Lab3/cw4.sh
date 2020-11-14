#!/bin/bash

x=1;
while [ $x -le 100000 ] ; do
	echo $x
	x=$[x+1]
	sleep 10
done
