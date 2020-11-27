#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void catch_wstrzymaj(int signum);
void catch_ignoruj(int signum);

void catch_zegar(int signum) {
    
    printf("wznowienie odbierania blokowanego sygnalu sygnalem %d\n", signum);
    signal(SIGCONT, catch_wstrzymaj);
}

void catch_zakoncz(int signum) {

    printf("komunikat i zakonczenie sygnalem %d\n", signum);
    exit(0);
}

void catch_komunikat(int signum) {

    printf("komunikat - sygnal %d\n", signum);
}

void catch_wstrzymaj(int signum) {

    int milisec = 0; 
    timer_t czas;
    struct itimerspec wartosc;
  
    wartosc.it_value.tv_sec = 1;
    wartosc.it_value.tv_nsec = milisec*1000000L;
    wartosc.it_interval.tv_sec = 0;
    wartosc.it_interval.tv_nsec = 0;

    timer_create(CLOCK_REALTIME, NULL,  &czas);
    timer_settime(czas, 0, &wartosc, NULL);

    printf("wstrzymanie odbierania %d\n", signum);
    signal(SIGALRM, catch_zegar);
    signal(SIGCONT, catch_ignoruj);
}

void catch_ignoruj(int signum) {}

int main() {

    int milisec = 100; 
    int i = 0;

    struct timespec opoznij = {0};
    opoznij.tv_sec = 0;
    opoznij.tv_nsec = milisec * 1000000L;
    //signal(SIGALRM, catchALRM);
    signal(SIGTERM, catch_zakoncz);
    signal(SIGUSR1, catch_komunikat);
    signal(SIGUSR2, catch_ignoruj); // wersja 2. do ignowrowania
    signal(SIGCONT, catch_wstrzymaj);   // wersja 1. do blokowania przez jakis czas
    
    while (1) {
        ++i;
        printf("%d %d\n", getpid(), i);
        nanosleep(&opoznij, (struct timespec *)NULL);
    } 
    return 0;
} 
