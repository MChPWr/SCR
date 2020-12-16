#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define ROZMIAR_NAZWY 32

int main() 
{
	char obr_map[] = "./obr_map";
	char nazwa_obr[ROZMIAR_NAZWY];
	int plik_fd, mapa_fd;
	struct stat plik;
	void *addr = NULL;

	stat("./obr_map", &plik);
	mapa_fd = open(obr_map, O_RDWR);
	addr = mmap(NULL, plik.st_size,PROT_WRITE | PROT_READ, MAP_SHARED, mapa_fd, 0);
	while(1)
	{
		printf("Podaj nazwę pliku z rozszerzeniem np. file.txt\n");
		printf("(zamknij program klawiszem 'q'):\n");
		scanf("%s",nazwa_obr);
		if(nazwa_obr[0] == 'q' && nazwa_obr[1]=='\0') // koniec programu
			break;
		plik_fd = open(nazwa_obr, O_RDONLY);
		while(plik_fd < 0)
		{
			printf("Nie otwarto pliku.\n");
			printf("Podaj nazwę pliku z rozszerzeniem np. file.txt\n");
			printf("(zamknij program klawiszem 'q'):\n");
			scanf("%s",nazwa_obr);
			if(nazwa_obr[0] == 'q' && nazwa_obr[1]=='\0') // koniec programu
				break;
			plik_fd = open(nazwa_obr, O_RDONLY);
		}
		mapa_fd = open(obr_map, O_RDWR);
		stat(nazwa_obr, &plik);
		addr = mmap(NULL, plik.st_size,PROT_WRITE | PROT_READ, MAP_SHARED, mapa_fd, 0);
		truncate(obr_map,plik.st_size);
		read(plik_fd, addr, plik.st_size);		
		close(plik_fd);
		close(mapa_fd);
	}
	munmap(addr, plik.st_size);
	return 0;
}


// Program wykonuje sie zgodnie z poleceniem.


