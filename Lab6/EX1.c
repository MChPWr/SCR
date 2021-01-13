#include <pthread.h>
#include <stdio.h>

#define N 20

/* funkcja wykonywana w wątku */
void* thread_func(void* thread_ID) {
    int * ID = (int * ) thread_ID;
	printf("Hello SCR. Written by thread %d \n", *ID);
    pthread_exit(NULL);
	return NULL;
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