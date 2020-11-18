#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void podpunktA()
{
	printf("podpunkt a.)\n");
	exit(0);
}





int main()
{
	signal(SIGTERM, podpunktA);

	int i=0;

	while(1){
		printf("%d", i++);
		sleep(1);
	}

	return 0;
}