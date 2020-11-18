#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

int stop = 0;

void przechwytywanie(int signum)
{
	if (stop == 0)
		switch (signum) 
		{
		case SIGALRM:
			printf("Przechwycono sygnal SIGALRM\n");
			exit(0);
			break;
		case SIGTERM:
			printf("Przechwycono sygnal SIGTERM\n");
			break;
		case SIGUSR1:
			stop = 1000;
			break;
		case SIGUSR2:
			break;	
		}	

}

int main()
{
	int i = 0;
	struct timespec tim, tim1;
	tim.tv_sec = 0;
	tim.tv_nsec = 500000000;

	signal(SIGALRM, przechwytywanie);
	signal(SIGTERM, przechwytywanie);
	signal(SIGUSR1, przechwytywanie);
	signal(SIGUSR2, przechwytywanie);

	while (1)
	{
		if (stop) --stop;
		i++;
		nanosleep(&tim, &tim1);
	}
}
