#include <stdio.h>
#include <pthread.h>

#define THR_NUM 8 //ilosc watkow

void *thread_print(void *id) {

	long thrid; //id
	
	thrid = (long) id;

    printf("Hello SCR. Written by thread ID: %ld\n", thrid); //zwracanie id watku wywolujacego funkcje
    pthread_exit(NULL); //zamkniecie watku wywolujacego
}

int main() {

    pthread_t id[THR_NUM]; //tablica watkow, ktorej rozmiar jest rowny ilosci watkow; pthread_t - typ id watkow
    int error; 

    for(int i = 0; i < THR_NUM; ++i) {
  
        error = pthread_create(&id[i], NULL, thread_print, (void *) id[i]);//tworzy nowy watek; NULL domyslne atrybuty;  na koncu arg przekazywany do funkcji

        //zwraca 0 gdy zostal stworzony poprawnie, gdy inna wartosc to niepoprawnie
        if(error != 0) 
            fprintf(stderr, "Creating thread failed"); //informacja gdy wystapil blad
    }

    pthread_exit(NULL);
} 
