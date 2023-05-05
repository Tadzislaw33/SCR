#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define PACKAGE_SIZE 256

int main(int argc, char *argv[]){

        int pipefd[2], count, filefd;
        pid_t pid;
        char buf[PACKAGE_SIZE];

        if(pipe(pipefd) == -1){
                perror("pipe");
                exit(-1);
        }

        pid = fork();

        if(pid < 0){
                fprintf(stderr,"Problem z procesem.\n");
                return -1;
        }else if(pid == 0){
                //a)
                close(pipefd[0]);
                if((filefd = open(argv[1], O_RDONLY)) < 0) {
                    perror("open");
                    exit(-1);
                }
                while((count = read(filefd, &buf, PACKAGE_SIZE)) > 0) {
                    if(write(pipefd[1], &buf, count) < 0) {
                        perror("write");
                        exit(-1);
                    }  
                }
                close(filefd);
        }else{
                //b)
                close(pipefd[1]);
                close(0);
                dup(pipefd[0]);
                close(pipefd[0]);
                if((execlp("display", "display", "-", NULL)) < 0) {
                    perror("open");
                    exit(-1);
                }
        }
}
