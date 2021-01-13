/******************************************************************************
* FILE: bug5.c
* DESCRIPTION:
*   A simple pthreads program that dies before the threads can do their
*   work. Figure out why.
* AUTHOR: 07/06/05 Blaise Barney
* LAST REVISED: 07/11/12
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
   int i;
   double myresult=0.0;
   printf("thread=%ld: starting...\n", (long)threadid);
   for (i=0; i<1000000; i++)
      myresult += sin(i) * tan(i);
   printf("thread=%ld result=%e. Done.\n",(long)threadid,myresult);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int rc;
long t;
for(t=0;t<NUM_THREADS;t++){
  printf("Main: creating thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
for(int t = 0; t < NUM_THREADS; t++)
  pthread_join(threads[t], NULL);
printf("Main: Done.\n");
pthread_exit(NULL);
}

// Wątek główny nie czekał na zakończenie wątków potomnych i kończył się przed nimi, więc wątki
// potomne były przerywane i nie mogły wykonać całej swojej pracy. Żeby pozwolić wątkom potomnym
// na prawidłowe wykonanie i zakończenie swojego działania wątek główny musi czekać, aż wszystkie
// wątki potomne zakończą swoje działanie. To oczekiwanie jest realizowane przez funkcję
// pthread_join() (dodano pętlę for w liniach 39 i 40). Gdy wszystkie wątki potomne się zakończą 
// wywołania funkcji thread_join() zostaną zakończone to wątek główny też może zostać zakończony.
// Zakończenie wątku jest realizowane przez funkcję pthread_exit(). Należy też dodać rzutowanie 
// void* na long w funkcji PrintHello.


