#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int main()
{
	char file_name[64];
	char output_file[] = "balbina.jpeg"; // piękna i zjawiskowa
	char *adres = NULL;
	int plik1, plik2;
	int pid = fork();

	if(pid == 0)
	{
		execlp("display", "display", "-update", "1", output_file, NULL);
	}


	else
	{
		while(1)
		{
			printf("Podaj nazwę pliku do odczytu \n");
			scanf("%s", file_name);
			plik1 = open(file_name, O_RDONLY);
		}
	}

	return 0;
}