#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define PACKAGE_SIZE 20

int main(int argc, char *argv[]){

        int pipefd[2], count, filefd;
        pid_t pid;
        char buf[PACKAGE_SIZE];

        /* a) utworzony potok */
        if(pipe(pipefd) == -1){
                fprintf(stderr,"Problem z potokiem\n");
                return -1;
        }
        /* b) podproces*/
        pid = fork();

        if(pid < 0){
                fprintf(stderr,"Problem z procesem.\n");
                return -1;
        }else if(pid == 0){
		                        close(pipefd[0]);
                        if((filefd = open(argv[1], O_RDONLY)) < 0){
                                perror("open");
                                exit(-1);
                        }
                        while((count = read(filefd, buf, PACKAGE_SIZE)) > 0){
                                if(write(pipefd[1], buf, count) < 0){
                                        perror("write");
                                        exit(-1);
                                }
                        }
                        close(pipefd[1]);
                        exit(EXIT_SUCCESS);

		
                close(pipefd[1]);
                while((count = read(pipefd[0], buf, PACKAGE_SIZE)) > 0){
                        write(1, buf, PACKAGE_SIZE);
                        write(1, " # ", 2*sizeof(char));
                }
                close(pipefd[0]);
                exit(EXIT_SUCCESS);
                }else{
                close(pipefd[1]);
                while((count = read(pipefd[0], buf, PACKAGE_SIZE)) > 0){
                        write(1, buf, PACKAGE_SIZE);
                        write(1, " # ", 2*sizeof(char));
                }
                close(pipefd[0]);
                exit(EXIT_SUCCESS);

                        close(pipefd[0]);
                        if((filefd = open(argv[1], O_RDONLY)) < 0){
                                perror("open");
                                exit(-1);
                                                while((count = read(filefd, buf, PACKAGE_SIZE)) > 0){
                                if(write(pipefd[1], buf, count) < 0){
                                        perror("write");
                                        exit(-1);
                                }
 
               }
}
