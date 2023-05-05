#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 5 //liczba watkow

void *thread_func(void *threadid){
    long tid = (long)threadid;
    printf("Hello world from thread %ld\n", tid);
    pthread_exit(NULL);
}

int main(int arc, char *argv[]){
    pthread_t id[NUM_THREADS];
    int error_code;

    for(long i = 0; i < NUM_THREADS; ++i){
        printf("creating thread %ld\n", i);
	error_code = pthread_create(&id[i], NULL, thread_func, (void *) i);

        if(error_code < 0){
            perror("pthread_create");
            exit(-1);
        }
    }
    for(int i = 0; i < NUM_THREADS; ++i){
        pthread_join(id[i], NULL);
    }
    pthread_exit(NULL);
}
