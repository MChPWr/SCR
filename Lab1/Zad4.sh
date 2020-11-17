#!/bin/bash

# zmienne srodowiskowe - jezeli program ma z nich korzystac nalezy je odkomentowac
#export CZAS=3
#export MASKA="*.sh"
#export ARCHIWUM=arch.tar

# Opis polecenia 'getopts' - lancuch opcji zawiera litery opcji do rozpoznania, dwukropek 
# oznacza koniecznosc podania argumentu opcji. (Uwaga: nalezy zwracac uwage na wykorzystanie 
# metaznakow - opis argumentow polecenia find na koncu skryptu)
while getopts "m:n:a:" opcja; do

	# Badanie kolejnych opcji przez 'case'.
  	case "${opcja}" in
    		m )  maska=${OPTARG};;
    		n )  czas=${OPTARG};;
    		a )  archiwum=${OPTARG};;
         
		# Badanie bledow.
	    	\? ) echo "Nieprawidlowa opcja: -${OPTARG}"
         	     exit;;
    		: )  echo "Nieprawidlowa opcja: -${OPTARG} wymaga argumentu"
         	     exit;;
  	esac
done

# Jezeli nie podano argumentu w wywolaniu skryptu.
if [ -z "$maska" ]; then
	# Przypisanie wyeksportowanej zmiennej srodowiskowej.
  	maska=$MASKA
	# Jezeli nie wyeksportowano zmiennej srodowiskowej.
  	if [ -z $MASKA ]; then
		# Dopoki nie podano odpowiedniego argumentu.
    		while [ -z "$maska" ]; do
			# Pytaj o podanie argumentu.
      			echo -e "\nPodaj maske nazwy pliku: "
			# Wczytaj argument.
      			read maska
    		done
  	fi
fi

# Jak wyzej
if [ -z $czas ]; then
  	czas=$CZAS
  	if [ -z $CZAS ]; then
    		while [ -z $czas ]; do
      			echo -e "\nPodaj liczbe dni od modyfikacji pliku: "
      			read czas
    		done
  	fi
fi

# Jak wyzej
if [ -z $archiwum ]; then
  	archiwum=$ARCHIWUM
  	if [ -z $ARCHIWUM ]; then
    		while [ -z $archiwum ]; do
      			echo -e "\nPodaj nazwe archiwum: "
      			read archiwum
    		done
  	fi
fi

# Na podstawie zadania 3.
tar -cvf $archiwum $(find . -type f -mtime -$czas -name "$maska")

#Flagi polecenia tar:
#	-c utworz nowe archiwum
#	-v wyswietl nazwy archiwizowanych plikow
#	-f uzyj nazwy archiwum podanej przez uzytkownika (uzytkownik podaje 
#	   pelna nazwe tzn. z rozszerzeniem)
# Argument $archiwum to nazwa archiwum.

# '.' w poleceniu 'find' oznacza bierzacy katalog.
#Flagi polecenia find:
#	-type  okresla rodzaj szukanych elementow ('f' dotyczy zwyklych plikow) 
# 	-mtime okresla maksymalna liczbe dni, ktore uplynely od ostatniej modyfikacji pliku
# 	-name  okresla pelna nazwe pliku 
# Argument $maska to nazwa pliku. Wszystkie metaznaki (np. '*') musza byc  
# poprzedzone znakiem '\', aby zachowaly swoje funkcje.
# Argument $czas to maksymalna liczba dni od ostatniej modyfikacji pliku.

