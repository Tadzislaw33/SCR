#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//2 - SRTF

void wczytaj(){
	FILE *fp= fopen("sched1.in", "r");
	char buf[1024];
	char krok, pid, pr, czas, wartosc;
	while(fgets(buf,1024,fp)){
		wartosc = sscanf(buf,&krok,&pid,&pr,&czas);
		if(wartosc==4){
			sscanf(buf,&pid,&pr,&czas);
		}
	//if 1 to nic 
	//if 4 to sscanf bez kroku 
 	//strtok znajduje spacje 
}
}

int main(){
//strok
//printf("%d",);

}
