#include <stdio.h>
#include <time.h>
#include <unistd.h>


/*
na poczatek kompiluje program poleceniem 
$ gcc zad1.c -o zad1
potem uruchamiam program poleceniem ./zad1
*/

//ponizej widac wynik pierwszej czesci zadania, uruchomiona nieskonczona
//petla z ++i, program zad1 jest w czolowce tych wykorzystujacych cykle obliczeniowe
//  PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND 
// 3845 jakub     20   0    2356    584    520 R 100,0   0,0   1:49.20 zad1 

//aby zmienic czestotliwosc odswiezania programu top klikam 'd' podczas dzialania programu i wprowadzam nowy czas odswiezania
//lub wywolujac program
//      $ top -d 1

//po dodaniu opoznienia program nie pojawia sie juz na szczycie listy top

int main (){
  
  int i=0, pid;
  pid = getpid();

  struct timespec ts, ts1;
  ts.tv_sec = 0;
  ts.tv_nsec = 100 * 1000000L;
  
  
  
  while(1){
    ++i;
    nanosleep(&ts, &ts1);
  }
  
  return 0;
}
