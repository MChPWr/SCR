#! bin/bash

# do wyświetlenia prostego menu
help() { echo "Help: $0 [-m <maska>] [-n <dni od modyfikacji>] [-a <archiwum>]"; exit 1;}

# inicjalizacja zmiennych globalnych
export mask=""
export time=""
export file=""


# pętla do pakowania plików wg zadanych parametrów
while getopts ":m:n:a" option; do
	case $option in
		m)
			mask="$OPTARG"
			;;	
		n)
			time="$OPTARG"
			;;		
		a)
			file="$OPTARG"
			;;
		*)
			help
			;;

	esac
done

# NAZWA MASKI
if [ ! $mask ]; 
	then echo "Podaj maske pliku: ";
	 read mask;
fi

# LICZBA DNI OD OSTATNIEJ MODYFIKACJI
if [ ! $time ]; 
	then echo "Podaj czas istnienia pliku: ";
	read time; 
fi

# PLIK DOCELOWY
if [ ! $file ];
	then echo "Podaj nazwe pliku docelowego: ";
	 read file; 
fi

# stworzenie archiwum z plików o zadanych parametrach
find . -type f -mtime -$time -name "$mask" | xargs tar  -czf $file.tar 