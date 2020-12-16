#include <iostream>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <fstream>

using namespace std;

int main()
{

    char n_pliku[100];
    bool good();
    struct stat stan_pliku;

    system("touch plik_zapis"); // polecenie systemowe tworzace plik  do zapisu

    while (true)
    {
        cout << "Podaj nazwe pliku do otwarcia" << endl;
        cin >> n_pliku;

        ifstream plik;
        ifstream plik_z;
        plik.open(n_pliku, ios::in | ios::out);
        if (plik.good() == false){
            cout << "Nie udalo sie otworzyc pliku" << endl;
            exit(1);
        }

        plik_z.open("plik_zapis", ios::in | ios::out);
        if (plik_z.good() == false)
        {
            cout << " Nie udalo sie otworzyc pliku plik_zapis" << endl;
            exit(1);
        }

        if(stat(n_pliku, &stan_pliku) == -1){
            cout  << "Bledne zczytanie stanu pliku  " << endl;
            exit(1);
        }

        // st_size -> aktualna wielkosc pliku

        truncate("plik_zapis",stan_pliku.st_size); // obcina obszar wymiany
        


    }

    return 0;
}