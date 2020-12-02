#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char* argv[])
{
 	int pipe_fd[2];
  	int c;
  	FILE *file;

  	pipe(pipe_fd);

  	if(fork()==0){
      	close(pipe_fd[1]);
      	close(0);

      	dup(pipe_fd[0]);
      	execlp("display", "display", "-", NULL);
   	}

   	close(pipe_fd[0]);

   	file=fopen(argv[1],"r");
   	if(file==NULL)
   		printf("File error\n");

   	while(!feof(file)){
        c=getc(file);
        write(pipe_fd[1], &c, 1);
    }
}

// Obraz wyswietli sie dopiero po zamknieciu potoku.