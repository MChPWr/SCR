#!/bin/bash

trap "echo trapped" {1..15}

while true
do
	date
	sleep 1
done
