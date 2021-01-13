#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void podpunktA()
{
	printf("podpunkt a.)\n");
	exit(0);
}


void podpunktB()
{
	printf("podpunkt b.)\n");
}


void podpunktC()
{
	printf("podpunkt c.)\n");
	for (int i = 0; i < 100; i++)
	{
		printf("%d \n", i);
		sleep(1);
	}
}

void podpunktD(){}


int main()
{
	signal(SIGTERM, podpunktA);
	signal(SIGALRM, podpunktB);
	signal(SIGUSR1, podpunktC);
	signal(SIGUSR2, podpunktD);

	int i=0;

	while(1){
		printf("%d", i++);
		sleep(1);
	}

	return 0;
}