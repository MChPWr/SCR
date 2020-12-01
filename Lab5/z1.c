#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 1000

int main(int argc, char const *argv[])
{
	int pid = fork();
	int tab[2];

	if(pid!=0)
	{
		const char* filename = argv[1];
		FILE *fptr;
		if((fptr = fopen(filename, "r")) == NULL)
		{
			fprintf(stderr, "%s\n", "Błąd otwarcia pliku");
			return 1;
		}

		char buffer[BUFFER];
		fgets(buffer, BUFFER, fptr);
		printf("Proces nadrzędny: %s", buffer);
		fclose(fptr);
		write(tab[1], buffer, sizeof(char)*BUFFER);
		close(tab[1]);
	}


	if(pid==0)
	{
		close(tab[1]);
		char buffer[BUFFER];
		read(tab[0], buffer, sizeof(char)*BUFFER);
        printf("Podproces: #%s #", buffer);
        close(tab[0]);
	}

	return 0;
}