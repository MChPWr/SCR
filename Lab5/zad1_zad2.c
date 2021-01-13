#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 512

int main() {

    pid_t pid;
    int fd[2], in_fd, n;
    char buf[BUF_SIZE];
    char file_name[32]; 
    
    if(pipe(fd) < 0) {

        fprintf(stderr, "Utworzenie potku nie powiodlo sie\n");
        return 1;
    }

    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Operacja fork nie powiodla sie\n");
    }

    if(pid == 0) {
        //dziecko
        close(fd[1]);
        close(0);
        dup(fd[0]);
        close(fd[0]);
        execlp("display", "display", "-", NULL);
    }
    else if(pid > 1){
        //rodzic
        close(fd[0]);
        printf("Podaj nazwe pliku wraz z rozszerzeniem (np. image.png | ~/Desktop/image.png):\n");
        scanf("%s", file_name);

        if((in_fd = open(file_name, O_RDONLY)) < 0) {
            
            fprintf(stderr, "Otwarcie pliku nie powiodlo sie\n");
            return 2;
        }
        
        while((n = read(in_fd, &buf, BUF_SIZE)) > 0) {
    
            if(write(fd[1], &buf, n) < 0) {
                fprintf(stderr, "Zapis do potoku nie powiodl sie\n");
                return 3;
            }  
        }
        close(in_fd);
    } 
}
