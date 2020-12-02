#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define ROZMIAR_BUFORA 128
#define ROZMIAR_NAZWY 32

int main(int argc, char *argv[]) 
{
    int potok_fd[2], plik_fd;    // deskryptory potoku, deskryptor pliku
    int pid;                     // pid nowego procesu 
    char bufor[ROZMIAR_BUFORA];
    int rozmiar_tekstu;          // rozmiar nowego tekstu w buforze
    char nazwa_pliku[ROZMIAR_NAZWY];
    
    if(pipe(potok_fd) < 0) 
    {   // gdy nie udalo sie utworzyc potoku
        fprintf(stderr, "Nie utworzono potoku.\n");
        return 1;
    }

    pid = fork(); // klonowanie potoku, zalozenie, że pid < 0 nie nastąpi
    
    if(pid == 0) 
    { // proces potomka
        close(potok_fd[1]);  // zamykanie niepotrzebnych deskryptorow od rodzica
        close(0);	      //
        dup(potok_fd[0]);    // przekierowanie zawartosci
        close(potok_fd[0]);
        
        // wywolanie programu "display" poleceniem z grupy exec*
        execlp("display", "display", "-", NULL);
    }
    else 
    {  // proces rodzica
        close(potok_fd[0]); // zamykanie niepotrzebnych deskryptorow
        
        if(argc >= 2) 
        { // gdy podano nazwe  pliku w argumencie 
            if((plik_fd = open(argv[1], O_RDONLY)) < 0) 
            {
	        	fprintf(stderr, "Nie otworzono pliku.\n");
	        	return 2;
        	}
        }
        else
        {  // w przeciwnym wypadku
        	printf("Podaj nazwę pliku z rozszerzeniem graficznym np. file.png:\n");
        	scanf("%s", nazwa_pliku);
        	if((plik_fd = open(nazwa_pliku, O_RDONLY)) < 0) 
        	{
		    	fprintf(stderr, "Nie otworzono pliku.\n");
		    	return 2;
        	}
        }	

       	write(1,"\n",2);
        while((rozmiar_tekstu = read(plik_fd, &bufor, ROZMIAR_BUFORA)) > 0) 
        {   // zapis do potoku
            if(write(potok_fd[1], &bufor, rozmiar_tekstu) < 0) 
            {
                fprintf(stderr, "Nie zapisano do potoku.\n");
                return 3;
            }  
        }
        //sleep(10); // program display uruchamia sie od razu, ale obraz wyswietla sie dopiero 
        //po zamknieciu potoku.
        close(potok_fd[1]); // zamykanie potoku i pliku 
        close(plik_fd);     // (ze strony potomka potok zamknie sie sam)
    } 
}

