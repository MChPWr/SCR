#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <csignal>
#include <cstdio>

int sem = 0;

void signalHandler(int signal) {
    if (signal == 14) {
        printf("Catching SIGALRM\n");
    }
    if (signal == 15) {
        printf("Catching SIGTERM\n");
        exit(1);
    }
    if (signal == 10) {
        printf("Catching SGUSR1. I'll not catch signals for ten iterations!\n");
        sem = 1;
    }
}

void milisecSleep(int* time) {
    struct timespec t_sleep = {
        *time / 100,
        (*time % 1000) * 1000000L};

    nanosleep(&t_sleep, NULL);
}

int main() {
    int timeDelay = 100;
    int counter = 0;

    signal(SIGUSR2, SIG_IGN);
    printf("PID: %d\n", getpid());

    for (int i = 0;; i++) {
        printf("%d\n", i);
        if (sem == 0) {
            signal(SIGALRM, signalHandler);
            signal(SIGTERM, signalHandler);
            signal(SIGUSR1, signalHandler);
        }

        if (sem == 1) {
            signal(SIGALRM, SIG_IGN);
            signal(SIGTERM, SIG_IGN);
            signal(SIGUSR1, SIG_IGN);

            if (counter < i) {
                counter = i + 10;
            }

            if (counter == i) {
                printf("Catching signals now!\n");
                sem = 0;
            }
        }

        milisecSleep(&timeDelay);
    }

    return 0;
}
