#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<fcntl.h>
#define rozmiar_paczki 100


int main(int argc, char const *argv[])
{
char bufor[rozmiar_paczki];
char nazwa_grafiki[25];
int  potok1, nr;
	
if(argc>1)
{
	fprintf(stderr, "%s\n", "BLAD");
	return 0;
}
	
pid_t dziecko;
//tworzenie potoku
int potok[2];
if (pipe(potok)==-1) 
{ 
	fprintf(stderr, "Blad tworzenia potoku\n" ); 
	return 0; 
} 
//dziecko
dziecko = fork();
if (dziecko == 0) {
        close(potok[1]);
        close(0);
        dup(potok[0]);
        close(potok[0]);  
        execlp("display","display","-",NULL);
    } 
    else 
    {
//rodzic
printf("Podaj pelna sciezke do pliku graficznego: \n");
scanf("%s", nazwa_grafiki);
close(potok[0]); 

if((potok1 = open(nazwa_grafiki, O_RDONLY)) < 0)  //tylko do czytania
{
	fprintf(stderr, "%s\n", "Nie udalo sie otworzyc pliku");
	return 0;
}

while((nr = read(potok1, &bufor, rozmiar_paczki)) > 0)
{
	write(potok[1],&bufor,nr);
}
close(potok1);
close(potok[1]);
wait(NULL); 
exit(EXIT_SUCCESS);
    }
return 0;
}
