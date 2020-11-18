#include<stdio.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>

void catch(int sig)
{
    printf("przeechwycono sygnał %d \n", sig);
    exit(0);
}





int main()
{
   int i=0;

   signal(SIGUSR1,catch);
   signal(SIGUSR2,catch);
   signal(SIGALRM,catch);
   signal(SIGTERM,catch);
   while(1)
   {
       i++;
   }
}