#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <fstream>
#include <time.h>
#include <unistd.h>

/*****************************************************************************************/
/*  - program w celu przetestowania trzeba w jednym terminalu uruchomić i w tym samym czasie w 
      drugim terminalu wywołać komendę tail -f /tmp/potok_1 
    - po uruchomieniu programu trzeba w pierwszym terminalu napisac komende rm /tmp/potok_1,
      aby móc ponownie otworzyc ten potok
    - efekt programu : w terminalu w ktorym uruchomimy komende tail -f zostanie wypisana zawartosc
      plikow tekstowych ktore otworzyl program
    - program nalezy uruchomic podajac jako argumenty nazwy plikow tekstowych np ./a.out tekst.txt */

#define FIFO "/tmp/potok_1" // zdefiniowanie zmiennej FIFO z lokalizacja do pliku 
                            // po wywolaniu programu trzeba wywolac komende rm /tmp/potok_1 aby moc powtornie wywolac program
using namespace std;

int main(int argc, char *argv[])
{

    // argc to liczba argumetnow, dla wywolania ./a.out tekst.txt argc=2
    //argv[0]=./a.out
    //argv[1]=tekst.txt

    int potok;

    if (mkfifo(FIFO, 0666) == -1)
    { // tworzy potok FIFO w lokalizacji /tmp/potok_1 i daje wlasciecielowie, grupie i wszystkim uprawnienia do odczytu i zapisu
        cout << "Nie udało się utworzyć potoku FIFO" << endl;
        exit(1);
    }
    else
    {
        cout << "Kolejka FIFO utworzona " << endl;

        if ((potok = open(FIFO, O_WRONLY)) == -1)
        {                                                   // otwarcie potoku w trybie odczytu
            cout << " Nie otoworzono potoku FIFO " << endl; // O_WRONLY - tryb pisania
            exit(1);                                        // O_RDONLY - tryb czytania
        }
        else
        {
            if (argc < 2)
            {
                cout << " Nie podano argumentow wywolania np tekst.txt" << endl;
                exit(1);
            }
            ifstream plik; // uchwyt do pliku
            bool good();

            cout << "Potok FIFO otwarty " << endl;

            for (int i = 1; i < argc; i++)
            {
                plik.open(argv[i], ios::out); // otwiera plik w trybie do odczytu
                if (plik.good() == true)      //plik otwarty prawidlowo
                {
                    char tmp;                       // zmienna pomocnicza
                    while (plik >> noskipws >> tmp) // dopoki w pliku sa dane
                    {                               //noskipws to manipultaor, ktory wplywa na strumien danych tak ze zapisywane sa same znaki
                        write(potok, &tmp, sizeof(tmp)); // wpisuje dane do potoku 
                    }

                    sleep(3);  // uspienie na 3s
                    plik.close();  // zamkniecie pliku 
                }
                else
                {
                    cout << "Nie udalo sie otworzyc pliku, sprawdz czy wpisana nazwa pliku jest poprawna" << endl;
                    exit(1);
                }
            }
        }
    }
    close(potok);
    return 0;
}