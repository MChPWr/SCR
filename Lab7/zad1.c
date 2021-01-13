#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 10

void *PrintHello(void  *threadid){
	long tid;
	tid = (long)threadid;
	printf("hello %d\n", tid);
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[NUM_THREADS];
	int rn;
	long t;

	for(t = 0; t < NUM_THREADS; t++){
		rn = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
	}
	pthread_exit(NULL);
}

/* Czy tego oczekiwaes?
	Nie, mozna byloby sie spodziewac tego, ze watki beda wykonywane
	w kolejnosci ich wywolywania tak jednak sie nie dzieje.
*/