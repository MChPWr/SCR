#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <fcntl.h> 
#include <sys/mman.h> 
#include <sys/stat.h> 

int main()
{
    int file, file2;
    char filename[100];
    struct stat status; //status pliku
    char *ptr; //zmapowany obszar

    while(1)
    {
        printf("Podaj nazwe pliku: \n"); //odpytanie uzytkownika o nazwe pliku
        scanf("%s", filename);

        file = open(filename, O_RDONLY); //otwieranie pliku
        file2 = open("plik",O_RDWR | O_CREAT); //utworzenie i otwarcie pliku do ktorego bedzie wpisywane

        if (stat(filename, &status) < 0) //gdy status jest nieprawidlowy
        { 
          printf("Blad \n");
          return(1);
        }

        ftruncate(file2, status.st_size); //ustawianie dlugosci pliku
        ptr = mmap(0, status.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, file2, 0); //mapowanie pamieci wspolnej
        read(file, ptr, status.st_size); //sczytuje linie z pliku do ptr o dlugosci bajtow = st_size
        msync(ptr, status.st_size, MS_SYNC); //synchronizuje plik z mapa pamieci
        munmap(ptr, status.st_size); //usuniecie/odmapowanie pamieci wspolnej

        close(file); //zamykanie pliku
    }

}