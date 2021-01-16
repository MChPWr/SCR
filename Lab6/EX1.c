#include <pthread.h>
#include <stdio.h>

#define N 20

/* funkcja wykonywana w wątku */
void* thread_func(void* thread_ID) {
    long ID = (long) thread_ID;
	printf("Hello SCR. Written by thread %ld \n", ID);
    pthread_exit(NULL);
}

int main(){

    pthread_t thread_ar[N];

    for(int i=0;i<N;i++){
        if(pthread_create(&thread_ar[i], NULL, thread_func, &thread_ar[i])) {
            fprintf(stderr, "Error creating thread\n");
            return 1;
        }
    }

    pthread_exit(NULL);
}

/*
Komentarz

Próbując wyświetlić ID wybranego wątku uznałem że muszę koniecznie skorzystać ze zmiennej pthread_t
która w teorii nazywana jest identyfikatorem wątku.

Jak się jednak okazało w przykładowym programie hello.c wykorzystywane było ID nadane przez użytkownika, czyli
po prostu kolejne numery wywolywanych wątków.

*/