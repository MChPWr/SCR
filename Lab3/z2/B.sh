echo "Jestem procesem B:"
echo "Uruchamiam proces C"
sh C.sh &
echo "Sleep 50s (B)"
sleep 50s
echo "Umieram! (B)"