#include <unistd.h>
#include<stdio.h> 
#include<signal.h> 
#include<stdlib.h>

void handle_some_signals(int sig) 
{ 
    switch (sig)
    {
    case SIGALRM:
        printf("Odebrano SIGALRM \n");
        exit(0);
        break;
    case SIGTERM:
        printf("Odebrano SIGTERM");
        break;
    case SIGUSR1:
        for(int j=0; j<1000;j++);
        break;
    case SIGUSR2:
        
        break;
    
    default:
        break;
    }
} 

int main(){
    int i=0;
    signal(SIGALRM, handle_some_signals);
    signal(SIGTERM, handle_some_signals);
    signal(SIGUSR1, handle_some_signals);
    signal(SIGUSR2, handle_some_signals);
    while(1){
        i++;
        printf("%d \n",i);
        usleep(500000);
    }
}
