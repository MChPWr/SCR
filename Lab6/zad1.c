#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
/***********************************************************************************************/
/* Oczekiwane bylo, ze program wypisze watki kolejno od 0 do 31. Jednak w praktyce 
   program wypisal watki zamieniajac w kilku (1-2) miejscach kolejnosc. Moze to byc spowodowane
   dzialaniem planisty systemu operaracyjnego                                                  */
/***********************************************************************************************/

#define N_thread 32

void *Write(void *ID)
{                                                          // funkcja tworzaca napis
    long thr_id = (long)ID;                                // przypisanie numeru ID do zmiennej typu long
    printf("Hello SCR. Written by thread %ld \n", thr_id); // wypisanie napisu na konsoli
    pthread_exit(NULL);                                    // zakonczenie watku
}

int main()
{
    // pthread_t - zmienna sluzaca do przechowywania identyfikatora watku
    pthread_t written_thread[N_thread]; // przechowanie tablicy identyfikatorow watkow

    for (long i = 0; i < N_thread; i++) // petla wywolujaca tworzenie watku
    {
        // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg) -> utworzenie watku
        // pthread_t *thread -> wskaznik do watku
        // const pthread_attr_t *attr -> parametry watku, NULL daje domyslne
        // void *(*start_routine) (void *) -> wskaznik na funkcje wykonywana przez watek (musi byc typu void* i zwaracac wynik  typu void *)
        // void *arg -> argument przekazywany funkcji start_routine

        int result = pthread_create(&written_thread[i], NULL, Write, (void *)i); // tworzenie watku
        if (result == 1)                                                         // jesli tworzenie nie udane to poinformuj o bledzie i zakoncz program
        {
            printf("Could not create thread. \n");
            exit(-1);
        }
    }

    pthread_exit(NULL); // wywolanie zakonczenia watku

    return 0;
}