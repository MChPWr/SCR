#!/bin/bash

#w ponizszym poleceniu wybieram flagi sygnalow UNIXa ktore chce blokowac
# 2 = SIGINT
# 3 = SIGQUIT
# 8 = SIGFPE
# 9 = SIGKILL

# przykladowo SIGINT spowoduje to ze nie uda sie zamknac programu naciskajac ^C (ctrl + c)
# sygnal SIGKILL nie moze byc zablokowany
trap `echo "TRAP";` 2 3 8 9

while true;
do
    date
    echo "PID: $$"
    sleep 1
done


