#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()

{
  int dis[2];
  char buff[100];
  struct stat filestat;
  char *ptr;
  
  if(fork()==0)
    {
      execlp("display","display","plik_wym", (char*) NULL);
    }

  while(1)
    {
      printf("Podaj nazwe pliku (q = wyjscie)\n");
      scanf("%s",buff);

      if(buff[0]=='q')
        return(0);

      dis[0]=open(buff, O_RDONLY,0);
      dis[1]=open("plik_wym", O_WRONLY,0);

      if(stat(buff, &filestat)<0)
        { 
          printf("problem");
          return(1);
        }

      ftruncate(dis[1], filestat.st_size);
      ptr=mmap(0,filestat.st_size,PROT_READ,MAP_SHARED, dis[1],0);
      read(dis[1], ptr, filestat.st_size);
      msync(0,filestat.st_size,dis[1]);
      close(dis[0]);
      close(dis[1]);
    }
}