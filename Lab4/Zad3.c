#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO "/tmp/potok"
#define ROZMIAR_BUFORA 128
#define ROZMIAR_NAZWY 32

int main(int argc, char *argv[]) 
{
    int potok_fd, plik_fd;           // deskryptor potoku, deskryptor pliku
    char bufor[ROZMIAR_BUFORA];
    int rozmiar_tekstu;              // rozmiar nowego tekstu w buforze
    char nazwa_pliku[ROZMIAR_NAZWY];
    int iterator = 1;                // potrzebny do liczenia argumentow wywolania

    
    if(argc == 1)  
    { // proces odczytu
		mkfifo(FIFO, 0666);              // stworzenie i otwarcie do odczytu procesu nazwanego
		potok_fd = open(FIFO, O_RDONLY); //
        
        // zapis do terminala
		while((rozmiar_tekstu = read(potok_fd, &bufor, ROZMIAR_BUFORA)) > 0) 
		{	  		
	  		//write(1,"#",1); // do wyswietlania '#' z zadania 1.
			write(1, &bufor, rozmiar_tekstu);
			//write(1,"#",1);
		}
		close(potok_fd);
    }
    else 
    {  // proces zapisu
    	mkfifo(FIFO, 0666);              // stworzenie i otwarcie do odczytu procesu nazwanego
		potok_fd = open(FIFO, O_WRONLY); //
        
        while(1)
		{
        	if(iterator < argc)
        	{ // gdy sa jeszcze niewykorzystane argumenty wywolania
                if(argv[iterator][0] == 'q' && argv[iterator][1] =='\0') // koniec programu
					break;
		        if((plik_fd = open(argv[iterator], O_RDONLY)) < 0) 
		        { // gdy nie znaleziono potoku
		    		fprintf(stderr, "Nie otworzono pliku.\n");
		    		return 2;
				}	
				iterator++;
			}
       		else 
       		{   // w przeciwnym wypadku
		    	printf("Podaj nazwę pliku z rozszerzeniem np. file.txt\n"); 
		    	printf("(zamknij program klawiszem 'q'):\n");
				scanf("%s", nazwa_pliku);
				if(nazwa_pliku[0] == 'q' && nazwa_pliku[1]=='\0') // koniec programu
					break;
				if((plik_fd = open(nazwa_pliku, O_RDONLY)) < 0) 
				{   // gdy nie znaleziono pliku
			    	fprintf(stderr, "Nie otworzono pliku.\n");
			    	return 2;
				}
			}
        
        	while((rozmiar_tekstu = read(plik_fd, &bufor, ROZMIAR_BUFORA)) > 0) 
        	{   // zapis do potoku
				if(write(potok_fd, &bufor, rozmiar_tekstu) < 0) 
				{
					fprintf(stderr, "Nie zapisano do potoku.\n");
					return 3;
				}  
			}
			close(plik_fd);  // zamykanie pliku
			sleep(3); 		 // czas przerwy
		}
		close(potok_fd); // zamykanie potoku
	}
    return 0;
}   

// Program wykonuje sie zgodnie z poleceniem i czeka kilkasekund przed wyslaniem kolejnego pliku.
// Dodano obsluge uzytkownika podczas dzialania programu, aby podal kolejne pliki lub zamknal 
// program. Program wspolpracuje rowniez z poleceniem 'tall'.
