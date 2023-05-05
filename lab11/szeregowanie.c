#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROCESSES 100

struct process{
    int arrival_time;
    int pid;
    int priority;
    int working_time;
    int remaining_time;
};

void srtf(struct process processes[], int n){
    int current_time = 0;
    int finished_processes = 0;

    while(finished_processes < n){
        int shortest_process = -1; // -1 bo bedzie przypisywany kolejny indeks procesu czyli dodatnie liczby 
        for(int i = 0; i < n; i++){
            //jesli czas rozpoczecia nowego procesu jest <= obecnemu i nowy proces ma jeszcze pozostaly czas
            if(processes[i].arrival_time <= current_time && processes[i].remaining_time > 0){ 
                //jesli nowy proces ma najkrotszy pozostaly czas dzialania
                if(shortest_process == -1 || processes[i].remaining_time < processes[shortest_process].remaining_time){
                    shortest_process = i; // nowy proces staje sie najkrotszym
                }
            }
        }
        //jesli nowy proces nie okazal sie krotszy to nadal wykonujemy obecny
        if(shortest_process == -1){
            current_time++;
        }
        //jest najkrotszy wiec sie wykonuje
        processes[shortest_process].remaining_time--;
        current_time++;
        printf("%d  %d\n", current_time, processes[shortest_process].pid);

        //jesli proces skonczyl prace to zwiekszamy licznik skonczonych procesow
        if(processes[shortest_process].remaining_time == 0){
            finished_processes++;
        }
    }
}

int main(){

    struct process processes[MAX_PROCESSES];
    int n = 7; //sched1 = 7 sched2 = 10
    char buf[1024];
    int h = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    
    FILE *file = fopen("sched1.in.txt", "r"); // NA KONCU ZADNEJ Z LINII PLIKU NIE MOZE BYC SPACJI
    
    if(file == NULL){
        perror("fopen");
        return 1;
    }

    while(fgets(buf,sizeof(buf),file)!=NULL){
	int counter=8;
        /*if(strlen(buf)==8 || strlen(buf)==9){
            sscanf(buf,"%d %d %d %d", &processes[h].arrival_time, &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            h++;
            k++;
            l++;
            m++;
        }*/
        if(strlen(buf)==2){
            sscanf(buf,"%d", &processes[h].arrival_time); 
            h++;
        }
        /*if(strlen(buf)==20){
            sscanf(buf,"%d %d %d %d", &processes[h].arrival_time, &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            h++;
            k++;
            l++;
            m++;
            sscanf(buf+8,"%d %d %d", &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            k++;
            l++;
            m++;
            sscanf(buf+14,"%d %d %d", &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            k++;
            l++;
            m++;
        }*/
        if(strlen(buf)>2){
	    isspace(buf);
            sscanf(buf,"%d %d %d %d", &processes[h].arrival_time, &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            h++;
            k++;
            l++;
            m++;
            sscanf(buf,"%d %d %d", &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            k++;
            l++;
            m++;
            sscanf(buf+counter,"%d %d %d", &processes[k].pid, &processes[l].priority, &processes[m].working_time);
            processes[m].remaining_time = processes[m].working_time;
            k++;
            l++;
            m++;

        }
            counter = counter+6;
            printf("%d\n",counter);

    }
	for(int i=0; i<h;i++){
		printf("%d\n",processes[i].arrival_time);	
	}
        for(int i=0; i<k;i++){
                printf("%d\n",processes[i].arrival_time);       
        }
        for(int i=0; i<l;i++){
                printf("%d\n",processes[i].arrival_time);       
        }
        for(int i=0; i<m;i++){
                printf("%d\n",processes[i].arrival_time);       
        }

    fclose(file);
    //srtf(processes, n);
    return 0;
}
