
#include <stdio.h>
#include <stdlib.h>
#define NUMOFTHREADS	3

void *Hello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello SCR. Written by thread %ld\n", tid);
   pthread_exit(NULL);
}

int main()
{
   pthread_t tabthreads[NUMOFTHREADS];
   long t;
   for(t=0;t<NUMOFTHREADS;t++){;
    pthread_create(&tabthreads[t], NULL, Hello, (void *)t);
     }
   pthread_exit(NULL);
}
