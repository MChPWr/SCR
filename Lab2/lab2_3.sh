#!/bin/bash

clear

find . -type f -mtime -2 -name "*.sh" -exec tar -rvf file.tar {} \;
	# find modified last 2 days with *.sh extention,
	# then compress to .tar 
	# -r - option appends to the archive instread of recreating it everytime
	# -f file.tar -  use archive file
	# -v - verbose output - output the list of results which are results of find

#find . -cmin -60 -type f -name "*.sh"
	# modified last hour