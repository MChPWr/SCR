#include <stdio.h>
#include <unistd.h>

int main(void){

	int i = 0;

	while(1){
		++i;
		sleep(0.10);
	}
}
