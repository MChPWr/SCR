#include <time.h>
#include <cstdio>

void milisecSleep(int* time) {
    struct timespec t_sleep = {
        *time / 100,
        (*time % 1000) * 1000000L};

    nanosleep(&t_sleep, NULL);
}

int main() {
    int timeDelay = 100;

    while (true) {
        printf("Hello World\n");
        milisecSleep(&timeDelay);
    }

    return 0;
}