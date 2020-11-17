#!/bin/bash

a=1;

while [ $a -le 100000 ] ; do
	a=$[ a + 1 ]
	sleep 1s
done

