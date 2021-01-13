#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>


int main()
{
	int plik1, plik2; // deskryptory
	char file_name[64];
	char output_file[] = "output.txt";
	struct stat status; 
	void *adres = NULL;


	while(1)
	{
		printf("Podaj nazwę pliku do odczytu \n");
		scanf("%s", file_name);
		plik1 = open(file_name, O_RDONLY);

		/* Obsługa błędów */
		while(plik1<1)
		{
			printf("Błąd odczytu pliku.\n Wprowadź nazwę pliku jeszcze raz:\n");
			scanf("%s", file_name);
			plik1 = open(file_name, O_RDONLY);
		}

		stat(file_name, &status); // pobranie statusu pliku do struktury
		plik2 = open(output_file, O_RDWR); // otwarcie 2 pliku przez deskryptor do mapowania
		truncate(output_file, status.st_size); // utworzenie tablicy o odpowiednim rozmiarze

		// zlecenie mapowania do pamięci
		adres = mmap(NULL, status.st_size, PROT_WRITE | PROT_READ, MAP_SHARED, plik2, 0);
		read(plik1, adres, status.st_size); // odczytanie rozmiaru pliku
		msync(adres, status.st_size, MS_SYNC); // synchronizacja danych zapisanych do odwzorowania

		close(plik1);
		close(plik2);
	}

	munmap(adres, status.st_size); // usunięcie mapowania
	return 0;
}