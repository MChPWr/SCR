#!/bin/bash

tar -cvf $3 $(find . -type f -mtime -$2 -name "$1")

#Flagi polecenia tar:
#	-c utworz nowe archiwum
#	-v wyswietl nazwy archiwizowanych plikow
#	-f uzyj nazwy archiwum podanej przez uzytkownika (uzytkownik podaje 
#	   pelna nazwe tzn. z rozszerzeniem)
# Argument $3 to nazwa archiwum.

# '.' w poleceniu 'find' oznacza bierzacy katalog.
#Flagi polecenia find:
#	-type  okresla rodzaj szukanych elementow ('f' dotyczy zwyklych plikow) 
# 	-mtime okresla maksymalna liczbe dni, ktore uplynely od ostatniej modyfikacji pliku
# 	-name  okresla pelna nazwe pliku 
# Argument $1 to nazwa pliku. Wszystkie metaznaki (np. '*') musza byc  
# poprzedzone znakiem '\', aby zachowaly swoje funkcje.
# Argument $2 to maksymalna liczba dni od ostatniej modyfikacji pliku.

