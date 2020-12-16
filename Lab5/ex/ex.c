#include <fcntl.h>    /* open() */
#include <stdio.h>    /* scanf()*/
#include <stdlib.h>   /* exit() */
#include <sys/mman.h> /* mmap(), munmap() */
#include <sys/stat.h> /* fstat() */
#include <unistd.h>   /* pipe(), fork() */

#define FILE_SIZE 128 /* Maksymalna dlugosc nazwy pliku */
#define CHILD_PROCESS 0 /* Proces dziecko */
struct stat fileStat; /* Dane zmapowanego pliku */

int main(void) {
    char fileName[FILE_SIZE];  /* Nazwa wczytywanego pliku */
    char* mapPtr;              /* Pamiec dla zmapowania plikow */
    int counter;               /* Licznik zczytanych bitow */
    int firstFile, secondFile; /* Deskryptory plikow */
    pid_t childProcess;        /* Do procesu potomnego */

    childProcess = fork(); /* Klonowanie procesu */

    if (childProcess < 0) { /* Nie udalo sie utworzyc podprocesu - wyjdz z programu */
        perror("Nie udało utworzyć sie podprocesu!\n");
        exit(-1);
    } else if (childProcess == CHILD_PROCESS) {                          /* ========Dziecko======== */
        execlp("display", "display", "-update", "1", "mapka.png", NULL); /* Wywolaj display i wyswietl obrazek z pliku 2 */
    } else {                                                             /* ===========Rodzic=========== */
        while (1) {
            printf("Podaj nazwe pliku do wyswietlenia lub wcisnij q aby zakonczyc program\n");
            scanf("%s", fileName);
            if (fileName[0] == 'q') /* Jesli q - skoncz program */
                break;

            firstFile = open(fileName, O_RDONLY); /* Otworz plik */

            if (firstFile != -1) {                                       /* Jesli poprawnie otwarty */
                fstat(firstFile, &fileStat);                             /* Pobiera info o pierwszym pliku do struktury */
                secondFile = open("map.png", O_RDWR);                    /* Otworz plik pamieci wspolnej */
                if (secondFile == -1) {                                  /* Jesli nie udalo sie otworzyc pliku */
                    perror("Nie udalo sie otworzyc pliku do wymiany\n"); /* Wyswietl komunkat */
                    exit(-2);                                            /* Wyjdz z programu */
                }

                ftruncate(secondFile, fileStat.st_size);                                                  /* Czysc i rezerwuj pamiec */
                mapPtr = mmap(NULL, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, secondFile, 0); /* Mapuj dane */
                if (mapPtr == MAP_FAILED) {                                                               /* Jesli nie udalo sie zmapowac - wyjdz z programu */
                    perror("Nie mozna dokonac mapowania");
                    exit(-3);
                }

                do { /*czytaj bity i kopjuj do mapowanej przestrzeni*/
                    counter = read(firstFile, mapPtr, fileStat.st_size);
                } while (counter > 0);

                if (msync(mapPtr, fileStat.st_size, MS_SYNC) == -1) { /* Jesli nie udalo sie zsynchronizowac-wyjdz z programu */
                    perror("Synchronizacja sie nie powiodla");
                    exit(-4);
                }

                munmap(mapPtr, fileStat.st_size); /* Zwolnij pamiec */
                close(firstFile);                 /* Zamknij 1 plik */
                close(secondFile);                /* Zamknij 2 plik */
            } else {                              /* Jesli nie otworzyl - wroc do poczatku whila */
                printf("Niewlasciwa nazwa pliku, sprobuj jeszcze raz\n");
            }
        }
    }

    return 0;
}
