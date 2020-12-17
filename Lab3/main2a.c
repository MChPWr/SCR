#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_(int sig){
	printf("Otrzymano sygnał\n");
	exit(0);
}

int main(){
	signal(SIGALRM, sig_);
	signal(SIGTERM, sig_);
	signal(SIGUSR1, sig_);
	signal(SIGUSR2, sig_);
		
	int i = 0;
	while(1){
		++i;
		sleep(0.1);
	}
	return 0;
}
