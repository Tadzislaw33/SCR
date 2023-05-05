u#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <string.h>

int main(){
    int fd[2];
    char file_name[100];
    char fsize[1024];
    struct stat struct_stat;
    char *ptr;

    if(fork()==0){
        sleep(2);
        execlp("display","display","fsize", (char*) NULL);
        //mmap(0,)
        //stat()
    }
    while(1){
        printf("Podaj nazwe pliku:\n");
        scanf("%s",file_name);
        fd[0]=open(file_name, O_RDONLY,0);
        fd[1]=open("fsize", O_WRONLY,0);
        if(stat(file_name, &struct_stat) < 0){ 
            perror("stat");
            exit(-1);
        }
        ftruncate(fd[1], struct_stat.st_size);
        ptr=mmap(0,struct_stat.st_size,PROT_READ,MAP_SHARED,fd[1],0);
        read(fd[1], ptr, struct_stat.st_size);
        msync(0,struct_stat.st_size,fd[1]);
        close(fd[0]);
        close(fd[1]);
    }
}
