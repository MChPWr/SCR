#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void podpunkt_a(int sygnal){
    printf("odebralem sygnal.Program konczy prace\n");  //wyswietla komunikat
    exit(0); // zakonczenie programu

}
void podpunkt_b(int sygnal){
    printf("Otrzymalem sygnal, ale pracuje normalnie\n "); // wyswietla komunikat

}
void podpunkt_c(int sygnal){
    signal(sygnal,SIG_DFL); // przywracanie do domyslnej akcji sygnalu
    for(int i=0; i<1001; i++){ //petla 1000 iteracji

    }
    printf("otrzymano sygnal i 1000 razy ziterowano petle\n"); //wyswietla komunikat
    raise(sygnal);
}
void podpunkt_d(int sygnal){
   // funkcja pusta bo nic nie robi, poprostu ignoruje sygnal 
}

int main(){

    signal(SIGTERM,podpunkt_a); // funkcja signal to cos jak trap, pierwszy argument to jaki sygnal wywoluje dzialania
                                // drugi argument to jakie dzialanie ma sie wykonac
    signal(SIGALRM,podpunkt_b);
    signal(SIGUSR1,podpunkt_c);
    signal(SIGUSR2,podpunkt_d);

    for(;;)
    {
        sleep(1);
    }

    return 0; 
}