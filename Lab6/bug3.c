/*****************************************************************************
* FILE: bug3.c
* DESCRIPTION:
*   This "hello world" Pthreads program demonstrates an unsafe (incorrect)
*   way to pass thread arguments at thread creation. Compare with hello_arg1.c.
* AUTHOR: Blaise Barney
* LAST REVISED: 07/16/14
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS     8

void *PrintHello(void *threadid)
{
   long taskid;
   sleep(1);
   taskid = *(long *)threadid; // usunięte wskaźniki
   printf("Hello from thread %ld\n", taskid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NUM_THREADS];
int rc;
long t;

for(t=0;t<NUM_THREADS;t++) {
  printf("Creating thread %ld\n", t);
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);  // usunięta referencja
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
   }

pthread_exit(NULL);
}

// Program wyświetlał taki sam numer ID wątku niezależnie od wątku (odczytywał wartość odpowiednią 
// dla referencji przez zbyt złożone rzutowanie). Należało usunąć referencję do t i wskaźniki z 
// przypisania threadid do taskid.
 
 
