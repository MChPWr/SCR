#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

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
	}

	return 0;
}