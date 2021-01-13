#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
int main()
{
	int des_pliku;  //deskryptor pliku
	int des_obszaru; //deskryptor obszaru
	char *adres, buff[1];
	struct stat status; //status pliku
	int poz; //zmienna do zmiany pozycji
	char nazwa_pliku [30];
	int i=0;
	if ((des_obszaru=open("map.txt",O_RDWR))<0) //otwieranie pliku do mapowania
	{
		fprintf(stderr, "Blad. Sprawdz czy istnieje plik do mapowania (map.txt) \n");
		exit -1;
	}
	while (1)
	{
		poz=lseek(des_obszaru,0,SEEK_END); //zmiana pozycji deskryptora obszaru, przesunięcie na rozmiar pliku (SEEK_END) +0  bajtów, czyli na koniec
		printf("Podaj nazwe pliku (aby zakonczyc wpisz k)\n");
		scanf("%s",nazwa_pliku);
		if (nazwa_pliku[0]=='k') //jeśli wpisze k - koniec
		{
			return 0;
		}
		if ((des_pliku=open(nazwa_pliku,O_RDONLY))<0) //otwieranie pliku, jeśli się nie uda - komunikat
		{
			fprintf(stderr, "Blad przy otwarciu pliku\n");
			exit -1;
		}
		else
		{
			if (fstat(des_pliku,&status)==-1) //pobieranie statusu pliku
			{
				fprintf(stderr, "Nie udalo sie uzyskac statusu pliku \n");
				exit -1;
			}
			adres=mmap(NULL, status.st_size+poz, PROT_WRITE | PROT_READ , MAP_SHARED, des_obszaru, 0); //mapowanie o odpowiednią pozycję, pamięć może być odczytywana lub zapisywana, MAP_SHARED - współdzielenie mapowania ze wszystkimi innymi procesami które mapują ten obiekt) 
			ftruncate(des_obszaru,status.st_size+poz); //ustawienie dlugosci pliku wskazanego przez deskryptor obszaru o dokładnie 'status.st_size+poz'
			if(adres==MAP_FAILED) 
			{
				fprintf(stderr, "Blad podczas mapowania\n");
				exit -1;
			}
			i=0;
			while(read(des_pliku,buff,1)>0) //wczytanie 1 bajta danych do otwartego pliku
			{
				adres[poz+i]=buff[0];
				i++;
			}
		}
	}
}
