#!/bin/bash

# Potrzebne programy
#sudo apt install mutt && sudo apt install sendmail

# Sciezka do katalogu z potrzebnymi plikami
PLIKI=$(pwd)/Zad2_pliki

# Dla kazdego maila z listy adresow.
for mail in $(cat $PLIKI/adresy.txt)
do

#	Wyslanie maila z tematem, trescia, zalacznikami i do adresata
	cat $PLIKI/tresc.txt | mutt -s "Okna PCV" -a $PLIKI/spec*.pdf -- $mail
	
done

