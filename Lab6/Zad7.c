#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NUM_THREADS 32

struct thread_data
{
	float pi;
};

void *Monte_Carlo(void *pi1)
{
        float x,y;
        float l,kwadrat=0,kolo=0;
   	struct thread_data *pi2;
   	pi2 = (struct thread_data *) pi1;
        srand48((unsigned)time(NULL));
        for(int i = 0; i < 500 ; i++)
        {
                x=drand48();
                y=drand48();
                l=sqrt(pow(fabs(x-0.5),2)+pow(fabs(y-0.5),2));
                if(l<=0.5) kolo++;
                kwadrat++;
        }
        pi2->pi = 4.0*kolo/kwadrat;
        printf("qwe: wartosc pi = %f %f %f\n",(float)pi2->pi,kolo,kwadrat);
        pthread_exit((void*)pi2);
}

int main(int argc, char *argv[])
{
        pthread_t id[NUM_THREADS];
        int blad; 
	struct thread_data pi[NUM_THREADS];
        float pi_estym=0,tmp;
        for(long i = 0; i < NUM_THREADS; i++)
        {
          	 pi[i].pi = 0;
                blad = pthread_create(&id[i], NULL, Monte_Carlo, (void *)&pi[i]);
                if(blad)
                        fprintf(stderr, "Blad tworzenia watku %ld.\n", i);
        }
        for(long i = 0; i < NUM_THREADS; i++)
                pthread_join(id[i], (void *)&pi[i]);

        for(long i = 0; i < NUM_THREADS; i++)
        {
                printf("Main: podproces %ld; wartosc pi = %f\n",i,(float)pi[i].pi);
                pi_estym=pi_estym+(float)pi[i].pi;
        }
        pi_estym=pi_estym/NUM_THREADS;
        printf("Main: proces glowny; wartosc pi = %f\n",pi_estym);

        pthread_exit(NULL);
}

