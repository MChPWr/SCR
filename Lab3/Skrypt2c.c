#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#include<time.h>
void catchignore(int sig)
{
    printf("przetwarzanie sygnału\n");
}


void catch(int sig)
{
    timer_t gman;
    struct itimerspec value;
  
    value.it_value.tv_sec = 2;
    value.it_value.tv_nsec = 5e08;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_nsec = 0;

    timer_create(CLOCK_REALTIME, NULL,  &gman);
    timer_settime(gman, 0, &value, NULL);

    signal(SIGALRM, catchignore);
}


int main()
{
   int i=0;
   
    struct timespec tim, tim2;

    tim.tv_sec  = 2;
    tim.tv_nsec = 5e08;

   signal(SIGUSR1,catch);
   signal(SIGUSR2,catch);
   signal(SIGALRM,catch);
   signal(SIGTERM,catch);
   while(1)
   {
       i++;
       sleep(1);
   }
}