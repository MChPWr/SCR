#include <unistd.h>
#include <stdio.h> 
#define BUFF_SIZE 32


int main(int argc, char *argv[]){
    if(argv[1] == NULL || argv[2] == NULL){   // sprawdzam czy podano wymagane argumenty wywołania
            fprintf(stderr, "ERR:  Nie podano nazwy pliku do przesłania" ); 
            return -1;
    }else{
        int pid=0;                  // do kontroli wartości zwracanej przez 
        int pfd[2];                 // file descriptor dla potoku
        char buffer[BUFF_SIZE];     // bufor do czytania wiadomości
        FILE *fp;

        if(pipe(pfd)==-1){          // sprawdzamy czy uda się stworzyć potok
            fprintf(stderr, "ERR:  Nie udało się utworzyć PIPE-a" ); 
            return -1; 
        };
        pid=fork();
        if(pid<0){                 // sprawdzamy czy fork się powiódł
            fprintf(stderr, "ERR:  Nie udało się utworzyć procesu dziecka" ); 
            return -1; 
        }else if(pid==0){          // jesteśmy dzieckiem 
            close(pfd[1]);
            read(pfd[0], buffer, BUFF_SIZE); 
        }else{                      // jesteśmy rodzicem
            close(pfd[0]);
        };
    };
}