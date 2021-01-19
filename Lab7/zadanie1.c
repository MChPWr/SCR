#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_THREADS 3

writeID(){
  long thread_ID = pthread_self();
  printf("Hello SCR! Written by thread %ld \n", thread_ID);
  pthread_exit(NULL);
}

int main(){
  pthread_t t_id[NUMBER_THREADS];
  for (int i = 0; i < NUMBER_THREADS; i++){
    pthread_create(&t_id[i], NULL, writeID, NULL);}

  pthread_exit(NULL);


}
