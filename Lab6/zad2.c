/******************************************************************************
* FILE: hello32.c
* DESCRIPTION:
*   A "hello world" Pthreads program which creates a large number of 
*   threads per process.  A sleep() call is used to insure that all
*   threads are in existence at the same time.  Each Hello thread does some
*   work to demonstrate how the OS scheduler behavior affects thread 
*   completion order.
* AUTHOR: Blaise Barney
* LAST REVISED: 01/29/09
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#define NTHREADS	32

void *Hello(void *threadid)
{
   int i;
   double result=0.0;
   sleep(3);
   for (i=0; i<10000; i++) {
     result = result + sin(i) * tan(i);
     }
   printf("%ld: Hello World!\n", (long int) threadid);
   pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
pthread_t threads[NTHREADS];
int rc; 
long t;
for(t=0;t<NTHREADS;t++){
  rc = pthread_create(&threads[t], NULL, Hello, (void *)t);
  if (rc){
    printf("ERROR: return code from pthread_create() is %d\n", rc);
    printf("Code %d= %s\n",rc,strerror(rc));
    exit(-1);
    }
   }
printf("main(): Created %ld threads.\n", t);
pthread_exit(NULL);
}

/*
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ gcc zad2.c -lpthread -lm
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
main(): Created 32 threads.
0: Hello World!
2: Hello World!
1: Hello World!
3: Hello World!
18: Hello World!
4: Hello World!
20: Hello World!
8: Hello World!
9: Hello World!
5: Hello World!
21: Hello World!
6: Hello World!
24: Hello World!
10: Hello World!
25: Hello World!
29: Hello World!
26: Hello World!
28: Hello World!
19: Hello World!
27: Hello World!
23: Hello World!
22: Hello World!
17: Hello World!
16: Hello World!
12: Hello World!
31: Hello World!
30: Hello World!
13: Hello World!
14: Hello World!
11: Hello World!
15: Hello World!
7: Hello World!
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
main(): Created 32 threads.
0: Hello World!
16: Hello World!
1: Hello World!
17: Hello World!
15: Hello World!
18: Hello World!
20: Hello World!
31: Hello World!
28: Hello World!
5: Hello World!
3: Hello World!
23: Hello World!
2: Hello World!
24: Hello World!
30: Hello World!
14: Hello World!
19: Hello World!
12: Hello World!
26: Hello World!
7: Hello World!
11: Hello World!
25: Hello World!
10: Hello World!
22: Hello World!
21: Hello World!
4: Hello World!
9: Hello World!
6: Hello World!
27: Hello World!
13: Hello World!
8: Hello World!
29: Hello World!
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ 


Kolejnosc w ktorej wyswietlane sa wyjscia watkow nie jest taka sama w kolejnych wywolaniach programu. Powodem jest losowe przydzielenie dostepu do procesora watkom.
*/

