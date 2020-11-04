#!/bin/bash

#wymagany program
sudo apt update && sudo apt install -y mutt

sciezka=$(pwd)/Zad2_pliki

for mail in $(cat $sciezka/adresy.txt)
do
    cat $sciezka/tresc.txt | mutt -s "Okna PCV" $mail -a $sciezka/spec*.pdf
done
