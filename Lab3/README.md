# README #

### Narzędzia Uniksa i pisanie skryptów (cd) ###


### Zadanie 1 ###
Działanie komendy ps jest widoczne na screenach. W chwili wywołania w moim systemie istniało 348 procesów.

### Zadanie 2 ###
Po zabiciu procesu aktywne zostają wszystkie procesy wyżej od niego w hierarchii (Po zabiciu B.sh umiera także C.sh).


### Zadanie 3 ###
Potok kilku wykonujących się przez dłuższy czas poleceń. W drugim terminalu poleceniem 'ps -f' można sprawdzić zależność między tymi procesami. Wszystkie są dziećmi basha.

### Zadanie 4 ###
Stworzyłem potok za pomocą komendy mknod fifo1 p
Następnie otworzyłem dodatkowe terminale (wszystkie w tym samym katalogu):
 - dwa przeznaczone do pisania w potoku 'cat > fifo1'
 - dwa przeznaczone do czytania z potoku 'cat fifo1'

Pisałem różne słowa na przemian w terminalach przeznaczonych do pisania. W terminalach do odczytu pojawiały się one losowo. 

Terminale skonczyly czekac na wprowadzanie i odczyt danych po zabiciu procesów.

### Zadanie 5 ###
trap przechwytuje wszystkie podstawowe sygnały. Tak napisanego procesu nie da się zabić sygnałem kill. 

### Zadanie 6 ###
Działanie sygnałów SIGTSTOP, SIGCONT, fg i bg pokazałem na screenach. Sygnał SIGCONT bardziej przypomina polecenie fg.

### Zadanie 7 ###
Za pomocą nice oraz renice można manipulować priorytetem procesów.