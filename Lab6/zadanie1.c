#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>


int main()
{
  char userInput[32];
  int desc1, desc2;
  struct stat status;
  void *adress = NULL;
  char *out_file = "out_file";

  while(1){
    //pytanie uzytkownika o nazwe pliku
    printf("Podaj nazwe pliku:");
    scanf("%s", userInput);
    desc1 = open(userInput, O_RDONLY);

    stat(userInput, &status);
    desc2 = open(out_file, O_RDWR);
    truncate(out_file, status.st_size);
    adress = mmap(NULL, status.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, desc2, 0);
    read(desc1, adress, status.st_size);
    msync(adress, status.st_size, MS_SYNC);
    
    close(desc1);
    close(desc2);
        }
  return 0;
}
