#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 10
#define M_PI 3.14159265358979323846

long double PI;
pthread_mutex_t PI_mutex;

void *myThreadFunc(void *vargp){
        sleep(1);
        int r = 1;
        int i = 0;
        long double myPI;

        time_t t;
        srand((unsigned) time(&t));

        //pola figur
        long double Pko = M_PI*r*r;
        long double Pkw = 4*r*r;

        int num = (Pkw * 10000) -1;
        int count_pko = 0;
        int count_pkw = 0;
        double x;
        double y;

        // - wylosuj punkt,
        for(int i=0; i <= num; i++){
                y = drand48();
                x = drand48();
                // - jeśli znajduje się on w kole, zwiększ licznik //punktów w kole,
                if( (x*x + y*y) <= r*r ) count_pko++;
                count_pkw++;// - dla każdego wylosowanego punktu zwiększ liczbę //punktów w kwadracie,- wróć do
        }
        long double lel =(long double)count_pko / count_pkw;
        myPI= (long double)4*lel;
        pthread_mutex_lock(&PI_mutex);
        PI=myPI;
        pthread_mutex_unlock(&PI_mutex);
}

int main(){
        pthread_t thread[NUM_THREADS];
        long double PIS[NUM_THREADS];
        long double ePI;
        pthread_mutex_init(&PI_mutex, NULL);
        printf("Main starting\n");

        for(int t=0; t<NUM_THREADS; t++){
                printf("Main: creating thread %d\n", t);
                int rc = pthread_create(&thread[t], NULL, myThreadFunc, (void *)t);
                if(rc){
                        printf("ERROR; return code from pthread_create() is %d\n", rc);
                        exit(-1);
                }
                pthread_join(thread[t], NULL);
                PIS[t] = PI;
                printf("Watek %d , PI=%Lf\n",t,PI);
                ePI=ePI+PI;
                PI=0;
        }
        pthread_mutex_destroy(&PI_mutex);
        printf("Main END PI=%Lf\n",(ePI/NUM_THREADS));
        exit(0);
}
