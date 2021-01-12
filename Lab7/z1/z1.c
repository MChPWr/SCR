#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_NUMBER 8

/* Funkcja do wypisywania ID wątku na standardowym wyjściu */
void *WypiszID(void threadID){
	long int ID = (long int) threadID;
	printf("Hello SCR. Written by thread: %d\n", ID);
	pthread_exit(NULL); 
}


int int main()
{
	pthread_t threads[THREAD_NUMBER]; // tablica wątków
	int result;
	long int ID;



	return 0;
}