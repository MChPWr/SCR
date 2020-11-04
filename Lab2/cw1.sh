#!/bin/bash

# wywołanie polecenia ps z flagą -f pokaże wyniki "full-format" w postaci
#    UID        PID  PPID  C STIME TTY          TIME CMD
echo -e " \n      ######################## \n Wykonanie polecenia ps -f \"full format\" \n "
ps -f


# wywołanie polecenia ps z flagą -l pokaże wyniki "full-format" w postaci
#    F S   UID   PID  PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
echo -e " \n      ######################## \n Wykonanie polecenia ps -l \"long\" \n "
ps -l


# wywołanie polecenia ps z flagą -u <EUID> pokaże procesy tylko wybranego użytkownika
USERNAME= `whoami`
echo -e " \n      ######################## \n Wykonanie polecenia ps -u $USERNAME \n "
ps -u $USERNAME


# wywołanie polecenia ps z flagą -t <TTY> pokaże procesy tylko uruchomione z danego terminala
TERMINAL= `tty`
echo -e " \n      ######################## \n Wykonanie polecenia ps -t $TERMINAL \n "
ps -t $TERMINAL

# wywołanie polecenia ps z flagą -p <PID> pokaże tylko proces o podanym PID
SOME_PID="358"
echo -e " \n      ######################## \n Wykonanie polecenia ps -p $SOME_PID \n "
ps -p $SOME_PID

# kod który sprawdza ile procesów uruchomił aktywny użytkownik
USERNAME=`whoami`
echo -e " \n      ######################## \n Wykonanie polecenia ps -u $USERNAME | wc | cut -f 6 -d ' ' \n "
ps -u $USERNAME | wc | cut -f 6 -d ' '

# kod który sprawdza ile procesów o pasującej nazwie sh istniało w momencie uruchomienia skryptu
# użyłem wyszukiwania po nazwie sh ponieważ nie znalazłem żadnego procesu sshd
echo -e " \n      ######################## \n Wykonanie polecenia  pgrep sh | wc | cut -f 5 -d ' ' \n "
pgrep sh | wc | cut -f 6 -d ' '

# zapis wyniku skryptu do pliku log
# ./cw1.sh > cw1_log.txt