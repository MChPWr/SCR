#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
	// strunktura dla nanosleep
	struct timespec tim, tim2;

	tim.tv_sec = 0;
	tim.tv_nsec = 500000000L;

	int i = 0;
	while(1){
		i++;
		//sleep(1);
		nanosleep(&tim, &tim2);
	}
}

// Bez opoznien proces natychmiastowo laduje w czolowce programu top ze zuzciem procesora
// na poziomie 99%. Wydaje mi sie ze dzieje sie tak z powodu tego ze proces wykonuje sie bardzo czesto.
// Po zastosowaniu opoznien proces nie pojawia sie w czolowce topu.

// Aby zwiekszyc czestotliwosc odsiwazania programu top nalezy wywolac go z -d oraz parametrem
// zadanym w sekundach
// top -d 0.5