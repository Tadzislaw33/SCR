#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>

//a
void sigalrm_hand(int sig){
}

//b
void sigterm_hand(int sig){
	printf("sygnal term wyjscie z programu\n");
	exit(1);
}

//c
void sigusr1_hand(int sig){
	printf("sygnal usr1 i powrot do programu\n");
}

//d
void sigusr2_hand(int sig){
	for(int i=0;i<1000;++i)
	printf("sygnal usr2\n");
// funkcja while dlugo wysiwetlac wstrzymac i wysylac i wstrzymac
}

int main(){

  printf("%d\n",getpid());
  struct timespec s, ms = {0, 100000};
   
  signal(SIGALRM,SIG_IGN); //a
  signal(SIGTERM,sigterm_hand); //b
  signal(SIGUSR1,sigusr1_hand); //c
  signal(SIGUSR2,sigusr2_hand); //d
  
  for(int i=0; ; ){
    i += 1;
    nanosleep(&s, &ms);
  }

return 0;
}
