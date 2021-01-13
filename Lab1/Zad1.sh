#!/bin/bash

LC_ALL=C

dzien=$(date +%w)

if [ $dzien -gt 5 ]; then

    echo "Weekend"
else

    echo "Dzien roboczy"
fi
