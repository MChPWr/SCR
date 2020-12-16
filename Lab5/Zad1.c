#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define ROZMIAR_NAZWY 32

int main() 
{
	char obr_map[] = "./obr_map";  // plik do mapowania obszaru pamięci
	char nazwa_obr[ROZMIAR_NAZWY]; // plik mapowany
	int plik_fd, mapa_fd;
	struct stat plik;              // struktura analizy pliku
	void *addr = NULL;             // adres pliku do mapowania 

	stat("./obr_map", &plik);      // wstępne mapowanie obszaru pamięci
	mapa_fd = open(obr_map, O_RDWR); // 
	addr = mmap(NULL, plik.st_size,PROT_WRITE | PROT_READ, MAP_SHARED, mapa_fd, 0); // 
	while(1)
	{
		printf("Podaj nazwę pliku z rozszerzeniem np. file.txt\n");
		printf("(zamknij program klawiszem 'q'):\n");
		scanf("%s",nazwa_obr);
		if(nazwa_obr[0] == 'q' && nazwa_obr[1]=='\0') // koniec programu
			break;
		plik_fd = open(nazwa_obr, O_RDONLY);
		while(plik_fd < 0) 
		{ // obsługa błędu otwarcia pliku w pętli do poprawnego wpisania nazwy lub
		  // zamknięcia programu
			printf("Nie otwarto pliku.\n");
			printf("Podaj nazwę pliku z rozszerzeniem np. file.txt\n");
			printf("(zamknij program klawiszem 'q'):\n");
			scanf("%s",nazwa_obr);
			if(nazwa_obr[0] == 'q' && nazwa_obr[1]=='\0') // koniec programu
				break;
			plik_fd = open(nazwa_obr, O_RDONLY);
		}
		 
		if((mapa_fd = open(obr_map, O_RDWR)) < 0) {
		    	fprintf(stderr, "Nie otworzono pliku.\n");
		    	return 2;
        	} // gdy plik mapowany zostanie otwarty można otworzyć plik do mapowania
		stat(nazwa_obr, &plik);  // analiza pliku 
		addr = mmap(NULL, plik.st_size,PROT_WRITE | PROT_READ, MAP_SHARED, mapa_fd, 0);
		// zajmowanie miejsca o odpowiednim rozmiarze
		// argumenty: kolejno adres początku mapy, wielkość pliku, uprawnienia, flagi,
		// deskryptor i początek odwzorowania pliku do mapy
		truncate(obr_map,plik.st_size);  
		read(plik_fd, addr, plik.st_size); 
		// czytanie z pliku połączone z zapisem do mapy		
		close(plik_fd);
		close(mapa_fd);
	}
	munmap(addr, plik.st_size); // zwolnienie pamięci przed końcem programu 
	return 0;
}

// Program wykonuje sie zgodnie z poleceniem, jeżeli plik obr_map istnieje w tym katalogu.
// Wszystkie pliki zostały prawidłowo przepisane do "obr_map" i po zmapowaniu były odpowiednio
// interpretowane ze względu na typ pliku.

