#include <fcntl.h>  /* open() */
#include <stdio.h>  /*scanf()*/
#include <stdlib.h> /* exit() */
#include <unistd.h> /* pipe(), fork() */

#define FILE_SIZE 128   /*Maksymalna dlugosc nazwy pliku*/
#define BUFFER_SIZE 512 /*Rozmiar Boforu obrazu*/
#define PIPE_WRITE 1    /*Pisanie do potoku*/
#define PIPE_READ 0     /*Odczyt z potoku*/
#define CHILD_PROCESS 0 /*Proces - dziecko*/

int main(void) {
    /*======================Rodzic========================*/

    char imageBuffer[BUFFER_SIZE]; /*Bufor obrazu*/
    char fileName[FILE_SIZE];      /*Nazwa wczytywanego pliku*/
    int somePipe[2];               /*somePipe[0] - odczyt, somePipe[1] - zapis*/
    int descriptor;                /*Deskrpytor pliku*/
    int bytesCounter;              /*Licznik zczytanych bajtow*/
    pid_t process;

    if (pipe(somePipe) < 0) { /*Tworzenie potoku, w przypadku błędu, wyjdz z programu*/
        exit(1);
    }

    printf("Type the name of the image you want to view\n");
    scanf("%s", fileName);
    descriptor = open(fileName, O_RDONLY);

    if (descriptor != -1) { /*Jesli udalo sie otworzyc plik*/
        process = fork();   /*Klonowanie procesu*/
        if (process < 0) {  /*Nie udalo sie utworzyc podprocesu - konczy program*/
            printf("Subprocess creation failed!\n");
            exit(1);
        } else if (process == CHILD_PROCESS) { /*========Dziecko========*/
            printf("I'm child \n");
            close(0);                           /*Zamkniecie stdin*/
            dup(somePipe[PIPE_READ]);           /*Duplikowanie czytania na stdin*/
            close(somePipe[PIPE_READ]);         /*Zamkniecie potoku do czytania*/
            close(somePipe[PIPE_WRITE]);        /*Zamkniecie do pisania*/
            execlp("display", "display", NULL); /*Wyswietlenie z stdin*/
            exit(0);
        } else { /*===========Rodzic===========*/
            printf("I'm parent\n");
            close(somePipe[PIPE_READ]);                                               /*Zamkniecie potoku do czytania*/
            while ((bytesCounter = read(descriptor, imageBuffer, BUFFER_SIZE)) > 0) { /*Czytanie bufora*/
                write(somePipe[PIPE_WRITE], imageBuffer, bytesCounter);               /*Wysylanie bufora do potoku*/
            }
            close(somePipe[PIPE_WRITE]); /*Zamknij potok do pisania*/
                                         //close(descriptor); /*Zamknij plik*/
        }
    } else { /*Jesli nie udalo sie otworzyc pliku - zakoncz program*/

        printf("Failed to open the file\n");
    }
    close(descriptor); /*Zamknij otwarty plik*/

    return 0;
}