#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int i=0;

void sigA(){
  printf("Komunikat o zakonczeniu pracy programu. \n");
  exit(0);
}

void sigB(){
  printf("Cos sie stalo, co wymaga twojej uwagi. \n");
}


void C(){
  printf("Program zostanie zatrzymany na 10 iteracji. \n");
  sleep(10);
  i=i+10;

}

void D(){
  ;
}

int main(){
  signal(SIGTERM, sigA);
  signal(SIGALRM, sigB);
  signal(SIGUSR1, C);
  signal(SIGUSR2, D);
  
  while(1){
    sleep(1);
    i++;
    printf("%d \n", i);
  }
}
