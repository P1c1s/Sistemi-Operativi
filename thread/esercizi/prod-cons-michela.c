#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<fcntl.h>
#include"provs.h"

#define titolo "Pippo.txt"

void* produttore(void*);
void* consumatore(void*);

Queue* coda;

void lettura();
void scrittura();
void stampa(Queue*);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(){
    srand(time(NULL));

    pthread_t prod, cons;

    coda = (Queue*) mmap(NULL, sizeof(Queue), PROT_WRITE | PROT_READ, MAP_ANON | MAP_SHARED, -1, 0);
    initializeQueue(coda);
    coda->numElementi = 0;

    pthread_create(&prod, NULL, produttore, NULL);
    pthread_create(&cons, NULL, consumatore, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    munmap(coda, sizeof(Queue));

    return 0;
}

void* produttore(void* args){

    while(1){
        pthread_mutex_lock(&mutex);

        stampa(coda);
        lettura();
        if(coda -> numElementi < 15){
            printf("Prima enqueue");
            enqueue(coda, rand()%100);
            printf("Seconda enqueue");
            enqueue(coda, rand()%100);
        }
        else
            printf("Coda piena\n");
        stampa(coda);
        printf("Arriva qui");
        scrittura();
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

void* consumatore(void* args){
    while(1){
        pthread_mutex_lock(&mutex);

        lettura();
        if(coda -> numElementi > 0){
            int eliminato = dequeue(coda);
            printf("\nEliminato il valore %d\n\n", eliminato);
        }
        stampa(coda);
        scrittura();
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    return NULL;
}

void lettura(){
    int fd = open(titolo, O_CREAT | O_RDONLY, S_IRWXU);
    if (fd < 0){
        fprintf(stderr, "Errore nell'apertura del file\n");
        exit(1);
    }

    char* letto = (char*) mmap(NULL, 3*sizeof(char), PROT_WRITE | PROT_READ, MAP_ANON, -1, 0);
    while(read(fd, letto, 3*sizeof(char)) > 0)
        enqueue(coda, atoi(letto));
    
    close(fd);
}

void scrittura(){

    printf("Arriva qui");
    int fd = open(titolo, O_CREAT | O_WRONLY, S_IRWXU);
    if (fd < 0){
        fprintf(stderr, "Errore nell'apertura del file\n");
        exit(1);
    }

    char* scritto = (char*) mmap(NULL, 3*sizeof(char), PROT_READ | PROT_WRITE, MAP_ANON, -1, 0);
    Node* nodo = coda->front;
    while(nodo != NULL){
        sprintf(scritto, "%d\n", nodo->data);
        int bw = write(fd, scritto, sizeof(scritto));
        nodo = nodo->next;
    }
}

void stampa(Queue* coda){
    Node* nodo = coda->front;

    if (coda->front == NULL)
        printf("Coda vuota\n");
    else{
        while (nodo != NULL) {
            printf("[%d]\n", nodo->data);
            nodo = nodo->next;
        }
        printf("Qui");
    }
}
