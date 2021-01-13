#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 512

int main() {

    pid_t pid;
    char buf[BUF_SIZE];
    
    if(pipe(fd) < 0) {

        fprintf(stderr, "Utworzenie potku nie powiodlo sie\n");
        return 1;
    }

    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Operacja fork nie powiodla sie\n");
    }