#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>


int main()
{
  char file_name[40];
  int plik[2]; //file descriptors
  struct stat buf;
  char *address=NULL;

    while(1)
     {
      //plik z ktorego bedzie pobrane
	printf("Podaj nazwe pliku \n");
	scanf("%s", file_name);
	plik[0] = open(file_name, O_RDONLY); //read only

	plik[1]= open("pamiec", O_CREAT | O_RDWR); //creat if does not exist //read&write
	
	//dlugosc pliku
	//fstat returns 0 if successful
	if (fstat( plik[0], &buf)==-1)
    		printf("was not successful\n");

	ftruncate(plik[1], buf.st_size); //obcina do wybranego obszaru obszar mapowany

	
	//rzutowanie mmap zmapowany obszar do wskaznika
	//The prot argument describes the desired memory protection
	//PROT_READ Pages may be read.
	//PROT_WRITE Pages may be written.
	//flaga
	//MAP_SHARED Share this mapping.
	
	address =( char *) mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, plik[1], 0);
	read(plik[0], address, buf.st_size);
	
	//msync - synchronizuje system plikow 
	msync(address, buf.st_size, MS_SYNC);
	
	close(plik[0]);
	close(plik[1]);
      }
    return 0;
}


/*

prezentacja dzialania programu

jakub@jakub-VirtualBox:~/Desktop/SCR/lab5$ gcc zad1.c 
jakub@jakub-VirtualBox:~/Desktop/SCR/lab5$ ./a.out 
Podaj nazwe pliku 
plik.txt
Podaj nazwe pliku 
^C
jakub@jakub-VirtualBox:~/Desktop/SCR/lab5$ chmod a+r pamiec 
jakub@jakub-VirtualBox:~/Desktop/SCR/lab5$ cat pamiec 
to jest plik

*/

