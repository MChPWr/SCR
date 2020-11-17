#!/bin/bash

# Zmienna lokalna LC_TIME okresla lokalna date i czas, ale bezpieczniej jest zmienic zmienna 
# nadrzedna LC_ALL, ktora nadpisuje pozostale zmienne. Podstawowa wartosc zmiennej LC_ALL to C.
# Ustawienie tej wartosci spowoduje takie samo dzialanie tego programu na kazdej maszynie
# UNIX-podobnej.

LC_ALL=C

# Polecenie 'locale' wyswietla wartosci zmiennych lokalnych.

# Odczytanie dnia tygodnia jako liczby od 1 do 7, gdzie 1 to poniedzialek.
DATA=$(date +%w)

# Sprawdzenie czy odczytana liczba jest mniejsza niz 6 (tzn. czy odcczytany dzien jest
# wczesniej niz w sobote).
if [ $DATA -lt 6 ]; then

#	Jezeli odczytana liczba jest mniejsza niz 6.
	echo "Dzien tygodnia (roboczy)"
else

#	Jezeli odczytana liczba jest wieksza niz 6.
	echo "Weekend"
fi

