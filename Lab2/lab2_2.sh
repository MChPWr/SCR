#!/bin/bash

clear

path=$(pwd)/files

for mail in $(cat $path/mails.txt)
do
	cat $path/message.txt | mutt -s "TOPIC" $mail -a $path/attachment.pdf
done

