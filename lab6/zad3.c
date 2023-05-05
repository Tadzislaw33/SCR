#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

#define FIFO "pipe"
#define PACKAGE_SIZE 16

int main(int argc,char *argv[]){

    int pipefd,filefd,count;
    char buf[PACKAGE_SIZE];
    mkfifo(FIFO, 0666);

    if((pipefd = open(FIFO,O_WRONLY)) == -1){
        perror("open");
        exit(-1);
    }
    while(--argc > 0){
        if((filefd = open(argv[argc],O_RDONLY)) < 0){
                perror("open");
                exit(-1);
        }
        while((count = read(filefd,buf,PACKAGE_SIZE)) > 0){
                if(write(pipefd,buf,count) < 0){
                        perror("write");
                        exit(-1);
                }
        }
        sleep(5);
        }
    close(pipefd);
}
