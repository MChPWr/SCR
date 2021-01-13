#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(){
	signal(SIGALRM, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, SIG_IGN);
		
	int i = 0;
	while(1){
		++i;
		sleep(0.1);
	}
	return 0;
}
