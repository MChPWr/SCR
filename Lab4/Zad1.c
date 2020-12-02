#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define ROZMIAR_BUFORA 32
#define ROZMIAR_NAZWY 32

int main(int argc, char *argv[]) {

    int potok_fd[2], plik_fd;    // deskryptory potoku, deskryptor pliku
    int pid;                     // pid nowego procesu 
    char bufor[ROZMIAR_BUFORA];
    int rozmiar_tekstu;          // rozmiar nowego tekstu w buforze
    char nazwa_pliku[ROZMIAR_NAZWY];
    
    if(pipe(potok_fd) < 0) { 
        fprintf(stderr, "Nie utworzono potoku.\n");
        return 1;
    }

    pid = fork(); // klonowanie potoku, zalozenie, że pid < 0 nie nastąpi
    
    if(pid == 0) { // proces potomka
        close(potok_fd[1]);
        close(0);
        
		while((rozmiar_tekstu = read(potok_fd[0], &bufor, ROZMIAR_BUFORA)) > 0) {
			write(1,"#",1);  // printf() wyswietla w terminalu '#' z opoznieniem
	  		write(1, &bufor, rozmiar_tekstu);
	  		write(1,"#",1);
		}
		write(1,"\n",2);
    }
    else {  // proces rodzica
        close(potok_fd[0]);
        if(argc >= 2) {
                if((plik_fd = open(argv[1], O_RDONLY)) < 0) {
            
            	fprintf(stderr, "Nie otworzono pliku.\n");
            	return 2;
        	}
        }
        else
        {
        	printf("Podaj nazwę pliku z rozszerzeniem np. file.txt:\n");
        	scanf("%s", nazwa_pliku);
        	if((plik_fd = open(nazwa_pliku, O_RDONLY)) < 0) {
            
		    	fprintf(stderr, "Nie otworzono pliku.\n");
		    	return 2;
        	}
        }	
       	write(1,"\n",2);
        while((rozmiar_tekstu = read(plik_fd, &bufor, ROZMIAR_BUFORA)) > 0) {
            if(write(potok_fd[1], &bufor, rozmiar_tekstu) < 0) {
                fprintf(stderr, "Nie zapisano do potoku.\n");
                return 3;
            }  
        }
        close(potok_fd[1]);
        close(plik_fd);
    } 
}
