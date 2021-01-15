#!/bin/bash


while getopts "n:m:a:" OPTION
do
    case $OPTION in
	n) LICZBA=$OPTARG;;
	m) ROZSZERZENIE=$OPTARG;;
	a) NAZWA=$OPTARG;;
	*) echo "Invalid option";;
    esac
done

if [ $OPTIND -eq 1 ]; then
    echo "No options were passed";
    exit 1;
fi

echo "liczba dni:   " $LICZBA
echo "rozszerzenie: " $ROZSZERZENIE
echo "output name:  " $NAZWA

find . -name *$ROZSZERZENIE -mtime -$LICZBA -exec tar -rvf $NAZWA {} +
