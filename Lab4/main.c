#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 64

int main(int argc, char *argv[]){
  int pid_num;
  int file_descriptor[2];

  pipe(file_descriptor);
  pid_num = fork();

  if(pid_num){
    char buff[MAX_BUFFER];

    while(read(file_descriptor[0], buff, MAX_BUFFER)){
      if(buff[MAX_BUFFER - 1] == 0) break;

      buff[MAX_BUFFER - 1] = '\0';
      printf("#%s#\n", buff);
    }
  }

  else{
    FILE *f = fopen(argv[1], "r");

    char buff[MAX_BUFFER];

    while(fgets(buff, MAX_BUFFER - 1, f)){
      buff[MAX_BUFFER - 1] = 1;
      write(file_descriptor[1], buff, MAX_BUFFER);
    }

    buff[MAX_BUFFER - 1] = 0;
    write(file_descriptor[1], buff, MAX_BUFFER);

    fclose(f);
  }
}

/*
Po skompilowaniu program wyświetlił zawartość paczki na terminalu:

amadeusz@amadeusz-VirtualBox:~/SCR/SCR/LAB2/SCR-1/Lab4$ ./program text.txt
#So long since I've seen her, she can feel a change in me.
#
#Change, she could feel a change in me.
#
#So long since I've seen her, she can feel a change in me.
#
#...
#
#Love comes with a price tag and a barcode.
#
#Still love you when we part though.
#
#Blame me like is'my fault.
#
#Walk around like your heart could.
#
#Hop around like your parkour.
#
#
#
#Zło to zło. Mniejsze, większe, średnie, wszystko jedno, pr#
#oporcje są umowne a granice zatarte (...), jeżeli mam wybier#
#ać pomiędzy jednym złem a drugim, to wolę nie wybierać wc#
#ale.
#
#Geralt w rozmowie z magiem Stregoborem.
#
#
#
#– Zapomniałem Ci podziękować...
#
#– Nie wam, panie, dziękować, ale mnie. To wy mnie żeście#
# ratowali, w mojej obronie ponieśliście uszczerbek. A ja? Co#
# ja takiego uczyniłem? Że człeka rannego, bez czucia, opatr#
#zyłem, na wóz pokładłem, nie dałem szczeznąć? To zwykł#
#a rzecz, panie wiedźmin.
#
#– Nie taka znowu zwykła, Yurga. Zostawiano mnie już... w p#
#odobnych sytuacjach... Jak psa...
#
#Kupiec, opuściwszy głowę, pomilczał.
#
#– Ano, cóż, paskudny otacza nas świat – mruknął wresz#
#cie. – Ale to nie powód byśmy wszyscy paskudnieli.
#
#rozmowa Geralta z kupcem Yurgą.
#
*/
