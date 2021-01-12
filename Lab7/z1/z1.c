#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUMBER 8

/* Funkcja do wypisywania ID wątku na standardowym wyjściu */
void *WypiszID(void *threadID){
	long int ID = (long int) threadID;
	printf("Hello SCR. Written by thread: %ld\n", ID);
	pthread_exit(NULL); // zakończenie wątku
}


int main()
{
	pthread_t threads[THREAD_NUMBER]; // tablica wątków
	int result;
	long int threadID;

	/* Tworzenie kolejnych wątków i wypisanie ich w konsoli */
	for(threadID=1; threadID<THREAD_NUMBER; threadID++)
	{
		result = pthread_create(&threads[threadID], NULL, WypiszID, (void *)threadID);
	}

	if(result != 0)
	{
		printf("ERROR %d\n", result);
		exit(-1);
	}

	pthread_exit(NULL); // ostatnia czynność głównego programu głównego

	return 0;
}