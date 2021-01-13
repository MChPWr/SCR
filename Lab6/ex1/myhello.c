#include <pthread.h>/*thread_*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_THREADS 5 /*Ilosc watkow*/

void* threadMessage(void* arg) /*Funkcja wyswietlajaca komunikat watku*/
{
    long threadId;
    threadId = (long)arg;
    printf("Hello from thread number: %ld \n", threadId);
    pthread_exit(NULL);
}

int main(void) {
    int thread;
    pthread_t threads[N_THREADS];

    for (long i = 0; i < N_THREADS; i++) {
        printf("Creating thread number: %ld \n", i);
        thread = pthread_create(&threads[i], NULL, threadMessage, (void*)i);
    }

    pthread_exit(NULL);
}
