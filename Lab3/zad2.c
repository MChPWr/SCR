#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <ucontext.h>

int counter = 0;


void catch(int sign) {
  if (sign == 14) {
    printf("zlapany SIGALRM: %d , koniec programu\n", sign);
    exit(0);
  }
  else if (sign == 15)
    printf("zlapany SIGTERM: %d , powrot do programu\n", sign);
  else if (sign == 10) {
    struct timespec tim, tim2;
    // tim.tv_sec = 2;
    // tim.tv_nsec = 0;
    // nanosleep(&tim, &tim2);
    counter = 1000;
    printf("zlapany SIGUSR1: %d , wstrzymywanie odebrania sygnału (np. na 1000 iteracji w pętli), i następnie wznowienie odebrania sygnału\n", sign);
    signal(SIGUSR1, SIG_IGN);
  }
  else if (sign == 12) {}  
}


int main (){

  int i=0, pid;
  pid = getpid();

  struct timespec ts, ts1;
  ts.tv_sec = 0;
  ts.tv_nsec = 100 * 1000000L;

  signal(SIGALRM, catch);
  signal(SIGTERM, catch);
  signal(SIGUSR2, catch);
  signal(SIGUSR1, catch);


  while(1){
    ++i;
    nanosleep(&ts, &ts1);
    printf("pid=%d  i=%d \n",pid,i);
    if(counter == 0) {
      signal(SIGUSR1, catch);
    }
    if(counter > 0) {
      counter--;
    }
  }

  return 0;
}
