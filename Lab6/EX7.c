#include <pthread.h>
#include <stdio.h>
#include <random>

#define N 20
#define POINTS_CHECKED 10000


/* funkcja wykonywana w wątku */
void* MonteCarloMethod(void* result_ptr) {
    long * pi = (long *) result_ptr;
    // Generator liczb losowych
    std::mt19937 gen{std::random_device{}()};
    // Rozklad jednorodny na przedziale -1.0 do 1.0
    std::uniform_real_distribution<double> {-1.0, 1.0};
	
    int points_in_square=POINTS_CHECKED;
    int points_in_circle=0;

    double x, y;

    for(int i=0; i < points_in_square; ++i)
    {
        x = losuj(gen);
        y = losuj(gen);
        if(x*x + y*y <= 1)
        {
            ++points_in_circle;
        }
    }
    *pi= 4.0 * points_in_circle / points_in_square;
    pthread_exit(NULL);
}

int main(){
    pthread_t thread[N];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    /* Initialize and set thread detached attribute */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(t=0; t<N; t++) {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&thread[t], &attr, MonteCarloMethod, (void *)t); 
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
            }
        }

    /* Free attribute and wait for the other threads */
    pthread_attr_destroy(&attr);
    for(t=0; t<N\; t++) {
        rc = pthread_join(thread[t], &status);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
            }
        printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
        }
    
    printf("Main: program completed. Exiting.\n");
    pthread_exit(NULL);
}
