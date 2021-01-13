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
   taskid = (long)threadid;
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
  rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t);
  if (rc) {
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
    }
   }

pthread_exit(NULL);
}

/*

przed zmiana w pliku:
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
Hello from thread 8
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ 



po zmianie dokonanej w pliku:
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
Creating thread 0
Creating thread 1
Creating thread 2
Creating thread 3
Creating thread 4
Creating thread 5
Creating thread 6
Creating thread 7
Hello from thread 0
Hello from thread 1
Hello from thread 3
Hello from thread 6
Hello from thread 2
Hello from thread 4
Hello from thread 5
Hello from thread 7
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ 


Zmieniono rzutowanie threadid na taskid
	linia 19
	taskid = *(long *)threadid;
	taskid = (long)threadid;
	
oraz zmieniono argument przekazywany w funkcji start_routine (polecenie pthread_create)
	linia 32
	rc = pthread_create(&threads[t], NULL, PrintHello, (void *) &t);
	rc = pthread_create(&threads[t], NULL, PrintHello, (void *) t);

*/
