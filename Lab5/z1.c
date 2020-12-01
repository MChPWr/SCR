#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define BUFFER 1000

int main(int argc, char const *argv[])
{
	int pid = fork();
	
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
	}


	if(pid==0)
	{
		// rób jakieś rzeczy
	}

	return 0;
}