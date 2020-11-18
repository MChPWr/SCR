#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sig_(int sig_num){
	printf("Signal occured\n");
}

int main(){
	signal(SIGALRM, sig_);
	
	int i = 0;
	while(1){
		++i;
		sleep(0.1);
	}
	return 0;
}
