#!/bin/bash

sudo apt-get update
sudo apt-get upgrade

sudo apt-get install mutt

source=$(pwd)/files_zad2

for mail in $(cat $source/adresy.txt)
do
    cat $source/tresc.txt | mutt -s "Okna PCV" $mail -a $source/spec*.pdf
done
