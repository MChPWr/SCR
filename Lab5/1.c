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
    pipe(potok);

    pid_t pid;
	pid = fork(); //utworzenie podprocesu
    
    if (pid < 0)
    {
        //blad
    }

    //rodzic - proces nadrzedny
	else if (pid > 0)
	{
        //zamyka koniec do odczytu
        //wpisuje writem

    }

    //dziecko - proces podrzedny
	else
	{
        //zamyka koniec do wpisywania
        //odczytuje readem
        //wyswietla na ekran

    }


}


