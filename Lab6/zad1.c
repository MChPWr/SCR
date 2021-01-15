#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void * printThread(void * ID){
  unsigned long int id = (unsigned long int) ID;
  printf("Hello SCR. Written by thread ID: %ld\n", id);
  //w tym miejscu nastepuje zakonczenie danego watku
  pthread_exit(NULL);
}

int main(){
  int error, liczba = 5; 
  unsigned long int i;
  pthread_t watki[liczba]; //tablica wskaznikow do poszczegolnych watkow 
  
  
  for(i=0; i<liczba; i++){
  /* pthread_create tworzy nowy watek
  	1. argument to wskaznik do watku
  	2. argument to parametry watku -> NULL
  	3. argument to wskaznik na funkcje wykonywana przez watek
  	   ta funkcja musi przyjmowac jeden argument typu void *
  	4. argument to element przekazywany funkcji start_routine
  */
  
    error = pthread_create(&watki[i], NULL, printThread,(void *) i); //zwraca 0 if OK
    if (error) {
      fprintf(stderr, "Error while creating thread");
    }
  }
  
  pthread_exit(NULL); //zakonczenie watku
  return 0;
}

/*
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ gcc zad1.c -lpthread
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
Hello SCR. Written by thread ID: 0
Hello SCR. Written by thread ID: 1
Hello SCR. Written by thread ID: 2
Hello SCR. Written by thread ID: 3
Hello SCR. Written by thread ID: 4
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
Hello SCR. Written by thread ID: 0
Hello SCR. Written by thread ID: 4
Hello SCR. Written by thread ID: 1
Hello SCR. Written by thread ID: 2
Hello SCR. Written by thread ID: 3
jakub@jakub-VirtualBox:~/Desktop/SCR/lab6$ ./a.out 
Hello SCR. Written by thread ID: 1
Hello SCR. Written by thread ID: 0
Hello SCR. Written by thread ID: 2
Hello SCR. Written by thread ID: 3
Hello SCR. Written by thread ID: 4

program wypisuje watki za kazdym razem w roznej kolejnosci

*/

