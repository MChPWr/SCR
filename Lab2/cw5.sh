#!/bin/sh

trap "echo \" \n NOT THIS TIME \n \"" HUP INT QUIT TERM STOP PIPE ALRM USR1 USR2 TTIN TTOU ILL FPE

while [ 1==1 ]
do
echo "hello world"
sleep 1
done