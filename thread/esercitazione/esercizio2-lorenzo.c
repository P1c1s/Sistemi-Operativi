#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
// #include <string.h>

pthread_mutex_t mutex;


void push(int fd){
    char* carattere = (char*)malloc(sizeof(char));
    int indice;
    int pila[10];
    if(read(fd, carattere, sizeof(char)) > 0)
        indice = atoi(carattere);
    else
        indice = 0;
    for(int i=0; i<indice; i++){
        read(fd, carattere, sizeof(char));
        pila[i] = atoi(carattere);
    }
    sprintf(carattere, "%d", indice);
    close(fd);
    
    fd = open("pila.txt", O_WRONLY | O_TRUNC, 0777);

    if(indice>-1 && indice<10){
        pila[indice] = rand()%10;
        indice ++;
        sprintf(carattere, "%d", indice);
        write(fd, carattere, sizeof(char));

        for(int i=0; i<indice; i++){
            sprintf(carattere, "%d", pila[i]);
            write(fd, carattere, sizeof(char));
        }
    }
    else
        printf("Pila piena\n");
}

void pop(int fd){
    char* carattere = (char*)malloc(sizeof(char));
    int indice;
    int pila[10];
    if(read(fd, carattere, sizeof(char)) > 0)
        indice = atoi(carattere);
    else
        indice = 0;
    for(int i=0; i<indice; i++){
        read(fd, carattere, sizeof(char));
        pila[i] = atoi(carattere);
    }
    sprintf(carattere, "%d", indice);
    close(fd);
    
    fd = open("pila.txt", O_WRONLY | O_TRUNC, 0777);

    if(indice>0){
        indice --;
        sprintf(carattere, "%d", indice);
        write(fd, carattere, sizeof(char));

        for(int i=0; i<indice; i++){
            sprintf(carattere, "%d", pila[i]);
            write(fd, carattere, sizeof(char));
        }
    }
    else
        printf("Pila vuota\n");
}

void* produttore(){
    while(1){
        usleep(1000*10*(rand()%100));
        pthread_mutex_lock(&mutex);
        int fd = open("pila.txt", O_CREAT | O_RDONLY, 0777);
        if(fd == -1){
            fprintf(stderr, "Errore apertura file");
            exit(1);
        }
        push(fd);
        close(fd);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void* consumatore(){
    while(1){
        usleep(1000*10*(rand()%100));
        pthread_mutex_lock(&mutex);
        int fd = open("pila.txt", O_CREAT | O_RDONLY, 0777);
        if(fd == -1){
            fprintf(stderr, "Errore apertura file");
            exit(1);
        }
        pop(fd);
        close(fd);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(){

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pthread_t threadProduttore;
    pthread_t threadConsumatore;

    pthread_create(&threadProduttore, NULL, produttore, NULL);
    pthread_create(&threadConsumatore, NULL, consumatore, NULL);

    pthread_join(threadProduttore, NULL);
    pthread_join(threadConsumatore, NULL);

    pthread_mutex_destroy(&mutex);
    printf("\n\n");

    return 0;
}