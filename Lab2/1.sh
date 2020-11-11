#!/bin/bash
LC_ALL=C

if [ $(date +%u) -gt 2 ]; then
    echo "weekend";
else
    echo "dzień roboczy";
fi
