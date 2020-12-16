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


	while(1)
	{
		printf("Podaj nazwę pliku do odczytu \n");
		scanf("%s", file_name);

		plik1 = open(file_name, O_RDONLY);
	

		stat(file_name, &status); // pobranie statusu pliku do struktury
		plik2 = open(output_file, O_RDWR); // otwarcie 2 pliku przez deskryptor do mapowania
		truncate(output_file, status.st_size); // utworzenie tablicy o odpowiednim rozmiarze
	}

	return 0;
}