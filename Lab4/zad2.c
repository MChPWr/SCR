#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int i;

void sygnal(int sig_num)
{
   switch (sig_num)
   {
   case SIGTERM:
       printf("Sygnal %d przechwycony\n", sig_num);
       _exit(0);
       break;
    case SIGALRM:
       printf("Sygnal %d przechwycony\n", sig_num);
       printf("Kontynuję\n");
       break;
    case SIGUSR1:
        break;
    case SIGUSR2:
        while (i++ < 1000);
        break;
   }
}

int main(int argc, char *argv[])
{
    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = sygnal;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGALRM, &action, NULL);
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);

    for(;;)
{
        i++;
        sleep(1);
}

    return 0;
}
