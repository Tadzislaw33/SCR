#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <openssl/evp.h>
#include <unistd.h>

#define MD5_LENGTH 33 
#define NUM_PASSWORDS 11     // dla test-data1 = 5, 2 = 11, 3 = 21, 4 = 28
#define NUM_DICT 14         // dla test-dict-mini  = 14, test-dict = 1000
#define NUM_DICT_ADD 140   // 20000
#define NUM_DICT_SUM 298  // 21000
#define DICT_NAME "test-dict-mini.txt"
#define DATA_NAME "test-data2.txt"

pthread_mutex_t lock;

// Struktura przechowujaca maile, hasla zahaszowane i nie zalezy co potrzeba 
typedef struct {
    char buffer[MD5_LENGTH];
}word;

word (* array) [NUM_PASSWORDS]; 

char found_passwords [MD5_LENGTH]; // Tu siedzi odhaszowane haslo urzytkownika
char emails [MD5_LENGTH]; // Tu siedzi email urzytkownika
int stop;                                 
char number[2];
int len;

// Przesuwanie stringa o jeden w prawo aby dodać cyfre na poczatku
void shift_string(char* word, size_t size){
    for(int i = size; i >= 0; i--)
        word[i+1] = word[i];
}

void bytes2md5(const char *data, int len, char *md5buf){
	EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
	const EVP_MD *md = EVP_md5();
	unsigned char md_value[EVP_MAX_MD_SIZE];
	unsigned int md_len, i;
    EVP_DigestInit_ex(mdctx, md, NULL);
	EVP_DigestUpdate(mdctx, data, len);
	EVP_DigestFinal_ex(mdctx, md_value, &md_len);
	EVP_MD_CTX_free(mdctx);
	for(i = 0; i < md_len; i++){
	    snprintf(&(md5buf[i * 2]), 16 * 2, "%02x", md_value[i]);
	}
}

// Funkcja sprawdzajaca czy kolejne hasla zgadzaja sie z ktoryms ze slownika 
// Producent tyle że nie jest watkiem
void compare(void* rows_void, word passwords[NUM_DICT_SUM], word passwords_hash[NUM_DICT_SUM]){
    long rows = (long) rows_void;

    for(int i = 0; i < NUM_DICT_SUM; i++){   
        for(int j = 0; j <= rows; j++){   
            if(strcmp(passwords_hash[i].buffer, array[1][j].buffer) == 0){   
                pthread_mutex_lock(&lock);
                strcpy(found_passwords, passwords[i].buffer);
                strcpy(emails, array[2][j].buffer);
                stop = 1;
                pthread_mutex_unlock(&lock);        
            }
        }             
    }
}

// Watek producenta ktory odpowiada tylko za male litery czyli podstawowa zawartosc slownika
void* Thread_1(void* rows_void){  
    word passwords[NUM_DICT_SUM];
    FILE *dictionary = fopen(DICT_NAME, "r");  
    word passwords_hash[NUM_DICT_SUM];
    char md5[MD5_LENGTH];  
    
    for(int i = 0; i< NUM_DICT; i++){
        fscanf(dictionary, "%s", passwords[i].buffer);
        //printf("%s\n", passwords[i].buffer);
    }    
    for(int i = 0; i < NUM_DICT; i++){   
        bytes2md5(passwords[i].buffer, strlen(passwords[i].buffer), md5);
        //printf("%s ======================> %s\n", passwords[i].buffer, md5);
        strcpy(passwords_hash[i].buffer, md5);                           
    } 
    compare(rows_void, passwords, passwords_hash);
    fclose(dictionary);                
    pthread_exit(NULL);
}

// Watek producenta ktory odpowiada tylko za dodanie cyfry na poczatku hasla ze slownika
void* Thread_2(void* rows_void){
    char md5[MD5_LENGTH];   
    word passwords[NUM_DICT_SUM];
    FILE *dictionary = fopen(DICT_NAME, "r");
    word passwords_hash[NUM_DICT_SUM];   
    int k = 0;

    for(int j = 0; j <= 9; j++){
        sprintf(number, "%d", j);
        for(int i = 0; i < NUM_DICT; i++){
            fscanf(dictionary, "%s", passwords[i].buffer);
            len = strlen(passwords[i].buffer);
            if(j==0){
                shift_string(passwords[i].buffer,strlen(passwords[i].buffer));
                passwords[i].buffer[0] = number[0];
            }
            else passwords[i].buffer[0] = number[0];
            //printf("%s\n", passwords[i].buffer);
            strcpy(passwords[k].buffer, passwords[i].buffer);
            k++;
        }
    }
    for(int i = 0; i < NUM_DICT_ADD; i++){   
        bytes2md5(passwords[i].buffer, strlen(passwords[i].buffer), md5);
        //printf("%s ======================> %s\n", passwords[i].buffer, md5);
        strcpy(passwords_hash[i].buffer, md5);                                
    } 
    compare(rows_void, passwords, passwords_hash);
    fclose(dictionary);                
    pthread_exit(NULL);
}

// Watek producenta ktory odpowiada tylko za dodanie cyfry na koncu hasla ze slownika
void* Thread_3(void* rows_void){
    char md5[MD5_LENGTH];
    word passwords[NUM_DICT_SUM];
    FILE *dictionary = fopen(DICT_NAME, "r"); 
    word passwords_hash[NUM_DICT_SUM];
    int k = 0;

    for(int j = 0; j <= 9; j++){
        sprintf(number, "%d", j);
        for(int i = 0; i < NUM_DICT; i++){
            fscanf(dictionary, "%s", passwords[i].buffer);
            len = strlen(passwords[i].buffer);
            if(j==0){
                passwords[i].buffer[len] = number[0]; 
                passwords[i].buffer[len + 1] = '\0'; 
            }
            else passwords[i].buffer[len-1] = number[0];
            //printf("%s\n", passwords[i].buffer);
            strcpy(passwords[k].buffer, passwords[i].buffer);
            k++;
        }
    }
    for(int i = 0; i < NUM_DICT_ADD; i++){   
        bytes2md5(passwords[i].buffer, strlen(passwords[i].buffer), md5);
        //printf("%s ======================> %s\n", passwords[i].buffer, md5);
        strcpy(passwords_hash[i].buffer, md5);                                
    } 
    compare(rows_void, passwords, passwords_hash);
    fclose(dictionary);                
    pthread_exit(NULL);
}

int main(){   

    stop = 0; 
    char character;
    int columns = 0;
    int rows = 0;

    // Wyzerowanie pamieci dla nowych hasel i emaili
    memset(found_passwords, 0, sizeof found_passwords); 
    memset(emails, 0, sizeof emails);  

    FILE *passwords_to_break = fopen(DATA_NAME, "r"); 
    array = (word(*)[NUM_PASSWORDS]) malloc(NUM_PASSWORDS * NUM_DICT_SUM * sizeof(word));

    if(array == NULL){
        perror("malloc: ");
        return -1;
    }

    while(character != EOF){
        fscanf(passwords_to_break, "%s", array[columns][rows].buffer);
        columns++;
        character = fgetc(passwords_to_break);
        if(character == '\n'){
            rows++;
            columns = 0;
        } 
    }

    pthread_t threads_id[3];
    long j = (long) rows;
    
    printf("Tworzenie watku 1\n");
    pthread_create(&threads_id[0],NULL,Thread_1,(void *)j);
    printf("Tworzenie watku 2\n");
    pthread_create(&threads_id[1],NULL,Thread_2,(void *)j);
    printf("Tworzenie watku 3\n");
    pthread_create(&threads_id[2],NULL,Thread_3,(void *)j);

    // Czekanie gdyby mialo dojsc do przerwania sygnalem
    for(int i = 1; i<1000000000; i++){ 
        if(stop == 1){
            pthread_mutex_lock(&lock);
            printf("Password for %s is %s\n", emails, found_passwords);
            memset(found_passwords, 0, sizeof found_passwords); 
            memset(emails, 0, sizeof emails);
            pthread_mutex_unlock(&lock);
            stop = 0;   
        }
    }
    
    for(int i = 0; i<=2; i++){
        pthread_join(threads_id[i], NULL);
        printf("Watek %d zakonczyl prace\n",i+1);
    }    

    pthread_exit(NULL);
    free(array);
    fclose(passwords_to_break);
    array = NULL;    
    return 0;
}