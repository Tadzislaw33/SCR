#include <stdio.h>
#include <time.h>

int main(){

  struct timespec s, ms = {0, 100000};
  for(int i=0; ; ){
    i += 1;
    nanosleep(&s, &ms);
  }

return 0;
}
