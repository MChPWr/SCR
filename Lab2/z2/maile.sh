#!/bin/sh
set `wc -l recipients.txt`
password="XXXXXXX"
email_sender="gorzelnik.p@gmail.com"
title="Instalacja okien PCV"
set `cat recipients.txt`

num=1;
echo $

# Pętla odpowiedzialna za wysyłanie emaili
while [ $num -le $# ] # less or equals
do
    sendEmail -f $email_sender \
    -t `sed -n ${num}p recipients.txt` \
    -a `find -name "spec*.pdf"` \
    -u "`echo $title`" \
    -m "` cat mail_content.txt`" \
    -s smtp-relay.gmail.com:465 \
    -xu `echo $email_sender` -xp `echo $password`
num=$(($num + 1))
done

exit