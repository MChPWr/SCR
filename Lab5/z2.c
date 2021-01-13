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
	int isEmpty;
	int pipe;
	char filename[64];

	if(pid>=0) // rodzic
	{
		FILE *fptr;
		printf("Podaj ścieżkę do pliku JPG/PNG\n");
		scanf("%s", filename);
		close(fd[1]);

		if((fptr = fopen(filename, "r")) == NULL)
		{
			fprintf(stderr, "%s\n", "Błąd otwarcia pliku");
			return 1;
		}

		isEmpty = read(pipe, &buffer, BUFFER);
	
		while(isEmpty>0){
			write(fd[1],&buffer,isEmpty);
		}

	close(pipe);
	}


	if(pid==0) // dziecko
	{
		close(fd[1]);
		dup(fd[0]); // tworzy duplikat istniejacego deskryptora pliku i przekazuje numer nowego deskryptora zwiazanego z tym samym plikiem lub laczem
        close(fd[0]);
	}


	return 0;
}