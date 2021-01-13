#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>

int main() {

  int file;
  int file_;
  char image[100];
  char *file_in_memory;
  struct stat filestat;

  if(fork() == 0){
     sleep(6);
     execlp("display", "", "-update", "1", "-delay", "2", "plik", NULL);
   }



   while(1){
  	printf("Nazwa pliku: ");
    scanf("%s", image);

    if((file = open(image, O_RDWR, S_IRUSR | S_IWUSR)) < 0 ) printf("Error");

    file_ = open("plik", O_RDWR | O_CREAT);
    if(fstat(file, &filestat) < 0) {
      printf("Error");
  	  return(1);
    }

    truncate("plik", filestat.st_size);
    file_in_memory = mmap(NULL, filestat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file_, 0 );
    read(file, file_in_memory,filestat.st_size);

    msync(file_in_memory, filestat.st_size, MS_SYNC);
    munmap(file_in_memory, filestat.st_size);
    close(file);
    }
}
