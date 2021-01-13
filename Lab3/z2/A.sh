#!/bin/bash

echo "Jestem procesem A:"
echo "Uruchamiam proces B"
sh B.sh &
echo "Sleep 50s (A)."
sleep 50s
echo "Umieram! (A)"