#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#define rozmiar_paczki 100

int main(int argc, char const *argv[])
{
char tekst[rozmiar_paczki];
if(argc<2)
{
	fprintf(stderr, "%s\n", "PODAJ NAZWE PLIKU PRZY WYWOLANIU PROGRAMU");
	return 0;
}
	
if(argc>2)
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
if (dziecko == 0) 
{
        close(potok[1]);
        while(read(potok[0],&tekst,rozmiar_paczki) != 0)
        {
            printf("# %s #\n",tekst);   
            for (int i=0;i<rozmiar_paczki;i++)
            {
                tekst[i]='\0';
            }  
        } 
        close(potok[0]);  
} 
else 
{
//rodzic
        const char* filename = argv[1];
	    FILE *fptr;
	    if((fptr = fopen(filename, "r")) == NULL)
	    {
	    	fprintf(stderr, "%s\n", "Nie udalo sie otworzyc pliku");
	    	return 0;
	    }

	char buffer[rozmiar_paczki];
        close(potok[0]); 
	    while(fgets(buffer, rozmiar_paczki, fptr)!=NULL)
        {
            write(potok[1],buffer,strlen(buffer));
        }
        fclose(fptr);
        close(potok[1]);
        wait(NULL);
        exit(EXIT_SUCCESS);
}
return 0;
}
