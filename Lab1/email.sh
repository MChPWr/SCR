#!bin/bash

path=$(pwd)/att

for main in $(cat $path/adresy.txt)
do
  cat $path/tresc.txt | mutt -s "PCV" $mail -a $path/spec*.pdf
done
