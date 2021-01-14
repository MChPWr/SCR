/******************************************************************************
* FILE: bug2.c
* DESCRIPTION:
*   A "hello world" Pthreads program that dumps core.  Figure out why and
*   then fix it - or else see the solution bug2fix.c.
* AUTHOR: 9/98 Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NTHREADS	8
#define ARRAY_SIZE      2000000

void *Hello(void *threadid)
{
   double A[ARRAY_SIZE];
   int i; 
   long tid;

   tid = (long)threadid;
   sleep(3);
   for (i=0; i<ARRAY_SIZE; i++)
   {
      A[i] = i * 1.0;
   }
   printf("%ld: Hello World!   %f\n", tid, A[ARRAY_SIZE-1]);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NTHREADS];
size_t stacksize;
pthread_attr_t attr;
int rc; 
long t;
pthread_attr_init(&attr);
pthread_attr_getstacksize (&attr, &stacksize);
printf("Thread stack size = %li bytes (hint, hint)\n",stacksize);
for(t=0;t<NTHREADS;t++){
  rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
  }
printf("Created %ld threads.\n", t);
pthread_exit(NULL);
}

// Błąd naruszenia ochrony pamięci przed zakończeniem wątku głównego jest spowodowany 
// nieprawidłową obsługą stosu przeznaczonego dla wątków potomnych. Rozmiar stosu jest ustawiony
// na domyślną wartość, a stos nie jest przekazywany do wątków potomnych. Żeby rozwiązać ten
// problem należy ustalić rozmiar stosu potrzebnego do wykonania poleceń przez dany wątek potomny
// i wprowadzić ten rozmiar do parametrów stosu przekazywanego do danego wątku, a dany stos
// przekazać do wątku w procesie tworzenia wątku poleceniem pthread_create(). Zeby można było
// sprawdzić rozmiar otrzymanego stosu wewnątrz wątku potomnego, funkcja Hello() wątku potomnego 
// musi mieć dostęp do deklaracji stosu, czyli stos musi zostać zadeklarowany globalnie lub 
// przekazany w postaci argumentu (np. w struktrze). Poprawnie działający program jest w pliku
// bug2fix.c.


