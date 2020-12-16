#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

using namespace std;

int main()
{

    char n_pliku[100];      // zmienna przechowujaca nazwe pliku
    struct stat stan_pliku; // struktura przechowujaca informacje o pliku
    int plik_zapisu;        // zmienna przechowujaca deskryptor pliku zapisu
    char *plik_pamiec;      // zmienna do pamieci mapowanej
    int plik;               // zmienna przechowujaca deskryptor pliku ktory jest otwierany

    system("touch plik_zapis"); // polecenie systemowe tworzace plik  do zapisu o nazwie plik_zapis

    if ((plik_zapisu = open("plik_zapis", O_RDWR)) == -1)
    { // Otwarcie pliku  do odczytu i zapisu
        cout << "Blad otwarcia pliku do zapisu" << endl;
        exit(1);
    }

    while (true) // nieskonczona petla
    {
        cout << "Podaj nazwe pliku do otwarcia" << endl;
        cin >> n_pliku; // zapisuje nazwe pliku do zmiennej

        if ((plik = open(n_pliku, O_RDWR)) == -1)
        { // Otwarcie pliku do odczytu i zapisu
            cout << "Blad otwarcia pliku o podanej nazwie" << endl;
            exit(1);
        }

        if (stat(n_pliku, &stan_pliku) == -1) // funkcja przypisujaca strukturze stan_pliku informacje o pliku o podanej nazwie
        {
            cout << "Bledne zczytanie stanu pliku  " << endl;
            exit(1);
        }

        // st_size -> aktualna wielkosc pliku

        truncate("plik_zapis", stan_pliku.st_size); // obcina obszar wymiany

        /* void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset); 
           start- adres odkad chcemy widziec odwzorowowanie pliku
           length - liczba bajtow jaka chcemy odwzorowac w pamieci
           prot - uprawnienia jakie chcemy nadac obszarowi pamieci : odczyt, zapis
           flags - dodatkowe flagi okreslajace sposob dzialnia wywolania mmap
                    MAP_SHARED -> udostepnia mapowanie
            fd - deskrytpor pliku ktory chcecemy odwzorowac w pamieci
            offser - liczba okreslajaca od ktorego miejsca chcemy rozpoczac odwzorowywanie */

        plik_pamiec = (char *)mmap(NULL, stan_pliku.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, plik_zapisu, 0);

        read(plik, plik_pamiec, stan_pliku.st_size); // zapisanie danych z pliku do pamieci mapowanej
        munmap(plik_pamiec, stan_pliku.st_size); // zwalnia mapowany obszar
        close(plik);
    }

    return 0;
}