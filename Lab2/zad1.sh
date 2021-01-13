# /bin/bash

# polecenie ps wyswietla opis biezacych procesow

# ps -f -> wyjscie w pelnym formacie, komenda uzyta z -L dodaje kolumny NLWP 
#          (liczba watkow) i LWP (ID watku)

# ps -l -> dlugi format

#EUID -> identyfikator uzytkownika
#PID -> identyfikator procesu
#TTY -> terminal do ktorego proces jest podlaczony
#TIME -> laczny czas procesora
#CMD -> nazwa pliku wykonywalnego

echo "ps -l"
#ps -l wyswietla F S UID PID PPID C PRI NI ADDR SZ WCHAN TTY TIME CMD
echo $(ps -l)

echo "ps -f"
#ps -f wyswietla UID PID C STIME TTY TIME CMD
echo $(ps -f)

echo "ps -u"
# ps -u -> wyswietla procesy uzywane przez uzytkownika
echo $(ps -u) 

echo "ps -t"
# ps -t -> wybiera procesy podlaczone do terminala
echo $(ps -t) 

echo "ps -p 1070"
# ps -p -> wybiera procesy ze wzgledu na identyfikator np. ps -p 42
echo $(ps -p 1070)
# wyswietla PID procesu rowne 1070 oraz jego TTY TIME i CMD 


# samo polecenie ps wywoluje u mnie dwa procesy:  bash i ps 