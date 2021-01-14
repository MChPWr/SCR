#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 32

void *hello(void *id) 
{
	printf("Hello SCR. Written by thread %ld\n", (long)id);
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) 
{
	pthread_t id[NUM_THREADS];
	int blad;
	long i;
	for(i = 0; i < NUM_THREADS; i++) 
	{
		printf("Tworzenie watku.\n");
		blad = pthread_create(&id[i], NULL, hello, (void *) i);
		if(blad) 
			fprintf(stderr, "Blad tworzenia watku %ld.\n", i);
	}
	for(i = 0; i < NUM_THREADS; i++) 
	{
		blad = pthread_join(id[i], NULL);
		if(blad) 
			fprintf(stderr, "Blad zakonczenia watku %ld.\n", i);
	}

	pthread_exit(NULL);
} 

// Wątki wykonują się w różnej kolejności w każdym wywołaniu programu i niezależnie od wątku 
// głównego. Po zwiększeniu liczby wątków można zauważyć, że, pomimo pseudolosowości wykonania
// wątków, wątki o bardzo małych indeksach wykonują się przed wątkami o bardzo dużych indeksach.
// To nie jest to czego, się spodziewałem.


