#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define DELAY 5e08


void catchtimer(int signum) {
    
    printf("continue prcoccessing signal...\n");
}

void catch1(int signum) {

    printf("hello, catched %d\n", signum);
    exit(0);
}

void catch2(int signum) {

    printf("hello, catched %d\n", signum);
}

void catch3(int signum) {

    timer_t gman;
    struct itimerspec value;
  
    value.it_value.tv_sec = 1;
    value.it_value.tv_nsec = 5e08;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    signal(SIGALRM, catchtimer);
}

void catch4(int signum) {
}

int main() {

    int i = 0;
    struct timespec tim, tim2;

    tim.tv_sec  = 0;
    tim.tv_nsec = DELAY;
    signal(SIGUSR1, catch3);
    signal(SIGUSR2, catch3);
    signal(SIGTERM, catch3);

    while (1) {

        ++i;
        printf("%d %d\n", getpid(), i);
        nanosleep(&tim, &tim2);
    } 
}