#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 1000

int main(int argc, char const *argv[])
{
	int pid = fork();
	int fd[2];
	char buffer[BUFFER];

	if(pid>=0)
	{
		const char* filename = argv[1];
		FILE *fptr;
		if((fptr = fopen(filename, "r")) == NULL)
		{
			fprintf(stderr, "%s\n", "Błąd otwarcia pliku");
			return 1;
		}

		fgets(buffer, BUFFER, fptr); // odczytanie kolejnych znakow ze strumienia i umieszczenie ich w tablicy znakowej buffer
		printf("Proces nadrzędny: %s\n", buffer);
		fclose(fptr); // zamkniecie pliku otwartego fopen()
		write(fd[1], buffer, sizeof(char)*BUFFER); 
		close(fd[1]);
	}


	if(pid==0)
	{
		close(fd[1]);
		read(fd[0], buffer, sizeof(char)*BUFFER);
        printf("Podproces: #%s #\n", buffer);
        close(fd[0]);
	}

	return 0;
}