#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<time.h>
#include<fcntl.h>

#define MAX 10


typedef struct file{
    int numRecord;
    int record[10];
} File;

void* produttore(void*);
void* consumatore(void*);

int letturaNumero(int);
void inserimento(File*);
void eliminazione(File*);
void scrittura(int, int);

pthread_mutex_t mutex;

int main(){
    pthread_t prod, cons;
    printf("\n");
    srand(time(NULL));

    char* titolo = "Pippo2.txt";

    pthread_create(&prod, NULL, produttore, (void*) titolo);
    pthread_create(&cons, NULL, consumatore, (void*) titolo);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}

void* produttore(void* argc){
    while(1){
        pthread_mutex_lock(&mutex);
        int fd = open((char*)argc, O_CREAT | O_RDONLY, S_IRWXU);
        if (fd == -1){
            fprintf(stderr, "Error occurred while opening the file\n");
            exit(1);
        }

        File* lettura = (File*) malloc(sizeof(File));

        lettura->numRecord = letturaNumero(fd);

        if (lettura->numRecord < MAX){
            for(int i=0; i<lettura->numRecord; i++){
                lettura->record[i] = letturaNumero(fd);
            }
            close(fd);
            inserimento(lettura);
        }

        fd = open((char*)argc, O_WRONLY | O_TRUNC, S_IRWXU);
        scrittura(fd, lettura->numRecord);
        for(int i=0; i<lettura->numRecord; i++){
            scrittura(fd, (lettura->record)[i]);
        }

        printf("\n[Pila : %d elementi]\t", lettura->numRecord);
        for(int i=0; i<lettura->numRecord; i++){
            printf("%d\t", (lettura->record)[i]);
        }
        printf("\n");
        
        close(fd);
        free(lettura);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void* consumatore(void* argc){
    while(1){

        pthread_mutex_lock(&mutex);
        int fd = open((char*)argc, O_CREAT | O_RDONLY, S_IRWXU);
        if (fd == -1){
            fprintf(stderr, "Error occurred while opening the file\n");
            exit(1);
        }

        File* lettura = (File*) malloc(sizeof(File));

        lettura->numRecord = letturaNumero(fd);
        
        if(lettura->numRecord == 0)
            printf("Empty stack. Waiting...\n"); 

        else if (lettura->numRecord < MAX){
            for(int i=0; i<lettura->numRecord; i++){
                (lettura->record)[i] = letturaNumero(fd);
            }
            close(fd);
            eliminazione(lettura);
        }

        fd = open((char*)argc, O_WRONLY | O_TRUNC, S_IRWXU);
        scrittura(fd, lettura->numRecord);
        for(int i=0; i<lettura->numRecord; i++){
            scrittura(fd, (lettura->record)[i]);
        }
        
        printf("\n[Pila : %d elementi]\t", lettura->numRecord);
        for(int i=0; i<lettura->numRecord; i++){
            printf("%d\t", (lettura->record)[i]);
        }
        printf("\n");

        close(fd);
        free(lettura);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int letturaNumero(int fd){
    char letturaChar;
    char* numero = (char*) malloc(4*sizeof(char));
        int byteLetti = read(fd, &letturaChar, sizeof(char));
    if(byteLetti == 0)
        return 0;

    while(letturaChar != '\n'){
        strcat(numero, &letturaChar);
        read(fd, &letturaChar, sizeof(char));
    }
    return atoi(numero);
}

void inserimento(File* lettura){

    int numero = rand()%90 + 10;
    printf("Prodotto : %d\n", numero);
    lettura->record[lettura->numRecord] = numero;
    lettura->numRecord += 1;
}

void eliminazione(File* lettura){
    printf("Consumato: %d\n", (lettura->record)[lettura->numRecord-1]);
    lettura->record[lettura->numRecord] = 0;
    lettura->numRecord -= 1;
}

void scrittura(int fd, int numero){
    char* stringa = (char*) malloc(4*sizeof(char));
    sprintf(stringa, "%d\n", numero);
    int scrittura = write(fd, stringa, strlen(stringa));
}

/*
    char* stringa = (char*) malloc(4*sizeof(char));
    sprintf(stringa, "%d\n", numero);
    int scrittura = write(fd, stringa, strlen(stringa));            //gestire caso errore

*/