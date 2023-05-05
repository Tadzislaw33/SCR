#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#define BABBLE_NAME "/Y01-42e"
#define BABBLE_MODE 0777
#define BABBLE_LIMIT 32
#define BABBLE_LENGTH 80

struct babblespace {
  pthread_mutex_t babble_mutex, m2;
  pthread_cond_t babble_cond;
  int babble_first, babble_total;
  char babbles[BABBLE_LIMIT][BABBLE_LENGTH];
};

int main(){
	struct babblespace * segment;
	int fd;
	char bufor[BABBLE_LENGTH] = "tdworeck";
    
	fd = shm_open(BABBLE_NAME , O_RDWR, BABBLE_MODE); 
	if(fd < 0){
		perror("shm_open");
		exit(-1);
	}

	segment = (struct babblespace *) mmap(NULL, sizeof(struct babblespace), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(segment == MAP_FAILED){
		perror("mmap");
		exit(-1);
	}
	printf("%d\n", segment -> babble_first);
	printf("%d\n", segment -> babble_total);

	pthread_mutex_lock(&segment -> babble_mutex);

	for(int n; n < BABBLE_LIMIT; n++){
		printf("%s\n", segment -> babbles[n]);
	}
	if((segment -> babble_total) < BABBLE_LIMIT){
		((segment -> babble_first+segment -> babble_total)% BABBLE_LIMIT) = bufor;
		++(segment -> babble_total);
	}
	if((segment -> babble_total) == BABBLE_LIMIT){
		bufor = segment -> babble_first;
		++(segment -> babble_first % BABBLE_LIMIT);
	}

	memcpy(segment -> babbles[9], bufor, BABBLE_LENGTH);
	pthread_mutex_unlock(&segment -> babble_mutex);

	return 0;

}


