#include <unistd.h>
#include <stdio.h> 
#include <fcntl.h>
#define BUFF_SIZE 16


int main(int argc, char *argv[]){
    int pid=0;                  // do kontroli wartości zwracanej przez 
    int pfd[2];                 // file descriptor dla potoku
    char buffer[BUFF_SIZE];     // bufor do czytania wiadomości
    int len;
    FILE *fptr;
    
    if(argv[1] == NULL ){   // sprawdzam czy podano wymagane argumenty wywołania
            fprintf(stderr, "ERR:  Nie podano nazwy pliku do przesłania" ); 
            return -1;
    };

    if (access(argv[1], R_OK) != 0) {   // sprawdzam czy podany plik istnieje i można go odczytać
        fprintf(stderr, "ERR:  Podany plik nie istnieje lub jest niemożliwy do odczytu" ); 
        return -1;
    };

    if(pipe(pfd)==-1){          // sprawdzamy czy uda się stworzyć potok
        fprintf(stderr, "ERR:  Nie udało się utworzyć PIPE-a" ); 
        return -1; 
    };

    pid=fork();
    if(pid<0){                 // sprawdzamy czy fork się powiódł
        fprintf(stderr, "ERR:  Nie udało się utworzyć procesu dziecka" ); 
        return -1; 

    ///////////  DZIECKO  /////////////////
    }else if(pid==0){              
        close(0);                   // zamykamy stdin
        dup(pfd[0]);                // file descriptor 0 (zazwyczaj stdin) wskazuje na pfd[0]
        close(pfd[1]);              // zamykamy koniec piszący potoku
        char * arguments[3];
        arguments[0]="display";
        arguments[1]=NULL;
        fprintf(stdout,"C:  Uruchamiam exec \n");
        execvp(arguments[0], arguments);
    ///////////  RODZIC  /////////////////
    }else{   
        close(pfd[0]);                      // zamykamy koniec czytający potoku
        int fileDesc[2];
        fileDesc[0] = open(argv[1], O_RDONLY);    // otwieramy plik do odczytu
        while(read(fileDesc[0], buffer, BUFF_SIZE)>0){  // czytamy dopóki są dane
            write(pfd[1], buffer, BUFF_SIZE);      // wysyłamy wiadomość do potoku 
        }; 
        fprintf(stdout,"P:  ZAMYKAM POTOK \n");
        close(pfd[1]);              // zamykamy koniec piszący potoku
        fprintf(stdout,"P:  POTOK ZAMKNIĘTY \n");
        close(fileDesc[0]);         // zamykamy czytany plik
    };
}