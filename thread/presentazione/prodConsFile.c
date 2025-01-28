#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

pthread_mutex_t mutex;

void* scrittura(void* arg){
    pthread_mutex_lock(&mutex);
    int* fd = (int*) arg;

    *fd = open("File.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

    if(*fd == -1){
        fprintf(stderr, "Errore creazione file per scrittura\n");
        close(*fd);
        exit(1);
    }

    char mex[] = "Writer";

    if(write(*fd, mex, 6*sizeof(char)) == -1){
        fprintf(stderr, "Errore nella scrittura\n");
        close(*fd);
        exit(1);
    }

    printf("\nSono il thread writer con TID: [%lu] e ho scritto sul file\n\n", pthread_self());

    close(*fd);
    
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void* lettura(void* arg){
    pthread_mutex_lock(&mutex);
    int* fd = (int*) arg;

    *fd = open("File.txt", O_RDONLY, S_IRWXU);

    if(*fd == -1){
        fprintf(stderr, "Errore creazione file per lettura\n");
        close(*fd);
        exit(1);
    }

    char* mex = (char*)malloc(6*sizeof(char));

    if(read(*fd, mex, 6*sizeof(char)) == -1){
        fprintf(stderr, "Errore lettura file");
        close(*fd);
        exit(1);
    }

    printf("\nSono il thread reader con TID: [%lu] e ho letto il messaggio del writer: \"%s\"\n\n", pthread_self(), mex);

    close(*fd);

    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

int main(){

    printf("Programma che crea due threads: uno scrive su un file e l'altro lo legge dallo stesso\n\n");

    int* fd;

    pthread_t writer;
    pthread_create(&writer, NULL, scrittura, (void*) fd);

    pthread_t reader;
    pthread_create(&reader, NULL, lettura, (void*) fd);

    pthread_join(reader, NULL);
    pthread_join(writer, NULL);

    return 0;
}