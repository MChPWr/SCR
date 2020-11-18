#!bin/bash

[ "$(date +%u)" -gt 5 ] && echo "Weekend" || echo "Dzień roboczy"
