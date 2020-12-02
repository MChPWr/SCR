#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

    // argc to liczba argumetnow, dla wywolania ./a.out tekst.txt argc=2
    //argv[0]=./a.out
    //argv[1]=tekst.txt

    int potok[2]; //potok[0] do odczytu, potok[1] do zapisu
    pid_t proces; // zmiena do tworzenia procesu

    if (pipe(potok) == -1) // stworzenie potoku
    {
        cout << "funkcja pipe zakonczona niepowodzeniem" << endl;
        exit(1);
    }

    proces = fork(); // stworzenie procesu

    if (proces < 0)
    {
        cout << "Funkcja fork zakonczona niepowodzeniem" << endl;
        exit(1);
    }
    else if (proces)
    {
        close(potok[0]); // zamkniecie potoku do odczytu
        cout << "Wywoluje proces macierzysty (nadrzedny)" << endl;

        if (argc < 2)
        {
            cout << "Nie podano nazwy pliku w wywolaniu programu" << endl;
            exit(1);
        }
        else
        {
            ifstream plik;
            bool good();
            plik.open(argv[1], ios::out); // otwiera plik w trybie do odczytu
            if (plik.good() == true)      //plik otwarty prawidlowo
            {
                cout << "Zapisuje dane z pliku do potoku " << endl;
                //close(potok[0]); // zamkniecie potoku do odczytu

                char tmp; // zmienna pomocnicza

                while (plik >> noskipws >> tmp) // dopoki w pliku sa dane
                {                               //noskipws to manipultaor, ktory wplywa na strumien danych tak ze zapisywane sa same znaki
                    write(potok[1], &tmp, sizeof(tmp));
                }

                plik.close();
            }
            else
            {
                cout << "Nie udalo sie otworzyc pliku, sprawdz czy wpisana nazwa pliku jest poprawna" << endl;
                exit(1);
            }
        }
    }
    else
    {
        close(potok[1]); // zamkniecie potoku do zapisu
        cout << "Wywoluje proces dziecko (proces potomny)" << endl;
        if (close(0) == -1)
        {
            ; // zwalnia dyskryptor pliku -> moze on byc powtornie przydzielony
            cout << " bledny dyskryptor zamykanego pliku" << endl;
        }
        dup(potok[0]);                           // tworzy duplikat istniejacego deskryptora pliku i przekazuje numer nowego dyskryptora zwiazanego z tym samym plikiem
                                                 // argumentem funkcji jest deskryptor pliku, ktory chcemy zduplikowac
        close(potok[0]);                         // zamkniecie potoku do odczytu
        execlp("display", "display", "-", NULL); // funkcja systemowa ktora uruchamia inny program
                                                 //pierwszy i drugi argument to nazwa programu display, trzeci argument to flaga, a ostatni zawsze jest rowny null
                                                 // moze tez byc wywolanie np execlp("ls","ls","-l",null)
    }

    sleep(3); // dopoki jest opoznienie, czyli proces matka dziala obrazek sie nie wyswietli

    return 0;
}