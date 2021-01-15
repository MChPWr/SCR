#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>


int main(){

  char nazwa_pliku[30], buffer[20];
  pid_t pid; //process identification, PID
  int fd[2]; //0 do czytania; 1 do pisania przechowuje dwie koncowki rury
  int deskryptor_pliku;

  
  //pipe(fd) passing info from one process to another
  if (pipe(fd) == -1) 
  { 
    fprintf(stderr, "Fail" ); 
    return 1; 
  }


  pid=fork();

  
  if(pid < 0){ //blad
    fprintf(stderr, "Fork failed." ); 
    return 1;
  }
  else if(pid == 0){ //dziecko
    close(fd[1]); 
    while (read(fd[0], buffer, 20) > 0) {
      write(1, "#",1);
      write(1, buffer, 20);
      write(1, "#",1);
    }      
  }
  else{ //pid > 0 rodzic
    printf("Podaj nazwe pliku:\n ");
    scanf("%s", nazwa_pliku);
    close(fd[0]);
    deskryptor_pliku = open(nazwa_pliku, O_RDONLY); 
    while (read(deskryptor_pliku, buffer, 20) > 0) //read == 0 for EOF
      write(fd[1], buffer, 20); //przekazanie potomkowi po literce do konca
    if(close(fd[1]) < 0){
      printf("Error while close");
      return 1;
    }
    
  }
  
  return 0;
}
