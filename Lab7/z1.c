#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS	4
#define REPEAT	10

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   int i = 0;
   for(i = 0; i < REPEAT; ++i)
   	printf("Hello SCR. Written by thread ID: %ld!\n", tid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   int rc;
   long t;
   for(t=0;t<NUM_THREADS;t++)
     {
     printf("Hello SCR. Written by thread ID: %ld\n", t);
     rc = pthread_create(&threads[t], NULL, PrintHello,(void *) t);
     if (rc){
       printf("Blad pthread_create() nr %d\n", rc);
       exit(-1);
       }
     }
   return 0;
}