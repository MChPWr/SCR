#!/bin/bash

export LC_ALL=C


DATA=`date | cut -d ' ' -f 1`

echo $DATA

#datas=$(date +%a)
#echo $datas

if [ $DATA = "Sun" ] || [ $DATA = "Sat" ]; then
    echo "it's not a working day"
else
    echo "it's a working day"
fi
