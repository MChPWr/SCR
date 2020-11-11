#!/bin/bash

time=$2
find ./ -iname "*.$1" -ctime -$2 -exec tar -rvf $3.tar {} \;
