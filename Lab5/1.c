#include <stdlib.h> 
#include <stdio.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <fcntl.h>

#define SIZE 100 //dowolnie dobrana wielkosc

int main (int argc, char* argv[])
{
    int potok[2];
    int id; //file descriptor
    char buffer[SIZE];
    char *filename = argv[1];

    if (pipe(potok) == -1) //utworzenie potoku funkcja pipe
	{		
		printf("Blad tworzenia potoku. \n");
	}

    pid_t pid;
	pid = fork(); //utworzenie podprocesu

    id = open(filename, O_WRONLY | O_APPEND);

    if (pid < 0)
 	{
		printf("Blad tworzenia procesu potomnego. \n");
	}

    //rodzic - proces nadrzedny
	else if (pid > 0)
	{
        close(potok[0]); //zamyka koniec potoku do odczytu

        if (argc != 2)
		{
			printf("Wymaganie jest podanie jednego argumentu. \n");
		}
 
        //wpisuje writem
        if (write(id, &buffer, SIZE) = 0) 
        {
            {
				printf("Nie udalo sie zapisac do potoku. \n");
			}
 
        }

    }

    //dziecko - proces podrzedny
	else
	{
		close(potok[1]); //zamyka koniec potoku do wpisywania
        //odczytuje readem
        //wyswietla na ekran

    }


}



