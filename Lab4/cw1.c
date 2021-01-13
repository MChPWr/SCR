#include <stdio.h>
#include <time.h>

int main()
{

	int i = 0;
	struct timespec tim, tim1;
	tim.tv_sec = 0;
	tim.tv_nsec = 500000000;

	while (1)
	{
		i++;
		nanosleep(&tim, &tim1);
	}
}
