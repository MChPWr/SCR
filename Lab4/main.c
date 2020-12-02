#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER 64

int main(int argc, char *argv[]){
  int pid_num;
  int file_descriptor[2];

  pipe(file_descriptor);
  pid_num = fork();

  if(pid_num){
    char buff[MAX_BUFFER];

    while(read(file_descriptor[0], buff, MAX_BUFFER)){
      if(buff[MAX_BUFFER - 1] == 0) break;

      buff[MAX_BUFFER - 1] = '\0';
      printf("#%s#\n", buff);
    }
  }

  else{
    FILE *f = fopen(argv[1], "r");

    char buff[MAX_BUFFER];

    while(fgets(buff, MAX_BUFFER - 1, f)){
      buff[MAX_BUFFER - 1] = 1;
      write(file_descriptor[1], buff, MAX_BUFFER);
    }

    buff[MAX_BUFFER - 1] = 0;
    write(file_descriptor[1], buff, MAX_BUFFER);

    fclose(f);
  }
}
