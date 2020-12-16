#/bin/bash

trap "echo trapped" 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

while true; do
    time=`date -u +%T`
    echo "$time"
    sleep 1
done




# Reakcje na sygnal wyslany za pomoca kill (bez trap)
# na sygnal SIGINT program zakonczyl swoje dzialanie
# na sygnal SIGQUIT program zakonczyl swoje dzialanie i pokazal się komunikat: wyjscie (zrzut pamieci)
# na sygnal SIGFPF program zakonczyl swoje dzialanie i pokazal się komunikat: blad w obliczeniach zmiennoprzecinkowych(zrzut pamieci)
# na sygnal SIGILL program zakonczyl swoje dzialanie  i pokazal sie komunikat: bledna instrukcja (zrzut pamieci)

# Po zostosowaniu polecenia trap program pokazuje komunikat trapped ale nie zabija procesu
# jedyny sygnal jaki jest nie obslugiwany to sygnal 9 SIGKILL