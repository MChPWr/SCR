#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {

    int milisec = 100; 
    int i = 0;

    struct timespec delay = {0};
    delay.tv_sec = 0;
    delay.tv_nsec = milisec * 1000000L;


    while (1) {
        ++i;
        printf("%d\n", i);
        nanosleep(&delay, (struct timespec *)NULL);
    } 
    return 0;
}
