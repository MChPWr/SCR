#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO "/tmp/pipe"

int main(){
	const int size = 128;
	int pipe_fd;
	int descriptor[10];
	int counter;			//liczba odczytanych bajtów
	char buffor[size];		//partie plików do przesyłania
	char file_name[64];		// nazwa otwieranego pliku
	
	printf("Tworze potok\n");		
	mkfifo(FIFO, 0666);
	printf("Utworzylem potok\n");
	pipe_fd = open(FIFO, O_RDWR);	
	printf("%d \n", pipe_fd);
	int i = 0;
	while(1)
	{
		printf("Podaj nazwę pierwszego pliku do odczytu (q = wyjscie):\t");
		scanf("%s", file_name);
		if(file_name[0] == 'q')
			break;
		descriptor[i] = open(file_name, O_RDONLY);
		if(descriptor[i] < 0)
			puts("Nie udalo sie otworzyc pliku");
	
		while ((counter=read(descriptor[i], buffor, size)) > 0)
		{
			write(pipe_fd, buffor, counter);
		}
		++i;
	}
	close(pipe_fd);
	return 0;
}
