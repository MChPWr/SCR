#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 100
#define POINTS_CHECKED 100000


/* funkcja wykonywana w wątku */
void* MonteCarloMethod(void* result_ptr) {
    double * pi = (double *) result_ptr;
    int points_in_square=POINTS_CHECKED;
    int points_in_circle=0;

    double x, y;

    for(int i=0; i < points_in_square; ++i)
    {
        x = 2.0*rand()/RAND_MAX - 1;
        y = 2.0*rand()/RAND_MAX - 1;
        if(x*x + y*y <= 1)
        {
            ++points_in_circle;
        }
    }
    *pi= 4.0 * points_in_circle / points_in_square;
    printf("PI = %lf \n", *pi);
    pthread_exit(NULL);
}

int main(){
    pthread_t thread[N];
    pthread_attr_t attr;
    double result[N];
    int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(t=0; t<N; t++) {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, MonteCarloMethod, (void *) &result[t]); 
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
            }
        }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for(t=0; t<N; t++) {
        rc = pthread_join(thread[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }


    double PI_estimation=0.0;
    for(int i=0; i<N; i++){
        PI_estimation+=result[i];
    };
    PI_estimation=PI_estimation/N;
    printf("Main: Final PI estimation calculated with Monte Carlo Method is  PI = %lf\n", PI_estimation);
    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}
