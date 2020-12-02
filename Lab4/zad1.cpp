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
    char bufor[BUFSIZ]; // tablica do odczyt

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
                close(potok[0]); // zamkniecie potoku do odczytu

                char tmp; // zmienna pomocnicza

                while (plik >> noskipws >> tmp) // dopoki w pliku sa dane
                {                               //noskipws to manipultaor, ktory wplywa na strumien danych tak ze zapisywane sa same znaki
                    write(potok[1], &tmp, sizeof(tmp));
                }

                plik.close();
                close(potok[1]);
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
        int licznik;
        cout << "Wypisuje zawartosc potoku :" << endl;
        while ((licznik = read(potok[0], bufor, BUFSIZ)) > 0) // czytanie z potoku do bufora
        {
            write(1, "# ", sizeof("# "));
            write(1, bufor, licznik);
            write(1, " #", sizeof(" #"));
        }
        cout<<endl;
        close(potok[0]);
    }

    return 0;
}