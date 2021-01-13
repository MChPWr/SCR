#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 4

void *printer(void *thread_id){
	long tid;
	tid = (long) thread_id;
	printf("Hello SCR! Written by thread #%ld!\n", tid);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	pthread_t threads[NUM_THREADS];
	
	int rc;
	long t;
	
	for(t = 0; t < NUM_THREADS; t++){
		printf("Thread created %ld\n", t);
		rc = pthread_create(&threads[t], NULL, printer, (void *)t);
	}
	
	pthread_exit(NULL);
}
