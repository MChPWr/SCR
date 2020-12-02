#include <unistd.h>
#include <stdio.h> 
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
        close(pfd[1]);              // zamykamy koniec piszący potoku
        while(read(pfd[0], buffer, BUFF_SIZE)>0){  // czytamy dopóki przychodzą wiadomości
            fprintf(stdout,"#%s#", buffer);        // wypisujemy wiadomość na stdout
        };      
        close(pfd[0]);              // zamykamy koniec czytający potoku
        fprintf(stdout,"\n");

    ///////////  RODZIC  /////////////////
    }else{   
        close(pfd[0]);              // zamykamy koniec czytający potoku
        fptr=fopen(argv[1],"r");    // otwieramy plik do odczytu
        do{
            // odczytujemy BUFF_SIZE-1 znaków lub do końca linii 
            if(fgets(buffer, BUFF_SIZE, fptr)==NULL){  
                fprintf(stderr, "ERR:  Błąd przy czytaniu z pliku" ); 
                return -1; 
            };
            write(pfd[1], buffer, BUFF_SIZE);  // wysyłamy wiadomość do potoku
        }while(feof(fptr)==0);                 // wykonujemy te operacje dopóki nie dotrzemy do końca pliku 
        close(pfd[1]);              // zamykamy koniec piszący potoku
        fclose(fptr);               // zamykamy czytany plik
    };
}