#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

#define DIM 5
pthread_mutex_t sediaBarbiere;
pthread_mutex_t attesa;

typedef struct Coda{
    pthread_t clienti[DIM];
    int front;
    int rear;
}Coda;

Coda sedie;

int isEmpty() {
    return sedie.front == -1;
}

int isFull() {
    return sedie.rear == DIM - 1;
}

void enqueue(unsigned long cliente) {
    if(isFull()){
        printf(RED "Tutte le sedie sono occupate, cliente perso\n" RESET);
        return;
    }
    if(isEmpty()){
        sedie.front = 0; // Imposta il front se è vuota
    }
    sedie.rear++;
    sedie.clienti[sedie.rear] = cliente;
    printf(YELLOW "Nuovo cliente arrivato %lu\n" RESET, sedie.clienti[sedie.rear]);
}

// Funzione per rimuovere un elemento dalla sedie
int dequeue() {
    if(isEmpty()){
        printf("Coda vuota! Impossibile rimuovere un elemento.\n");
        return -1; // Valore di errore
    }
    unsigned long cliente = sedie.clienti[sedie.front];
    if(sedie.front >= sedie.rear){
        // Se c'è solo un elemento, resetta la sedie
        sedie.front = -1;
        sedie.rear = -1;
    }else 
        sedie.front++;
    return cliente;
}

void* cliente(void* arg){
    pthread_mutex_lock(&attesa);
    enqueue(pthread_self());
    pthread_mutex_unlock(&attesa);
    return NULL;
}

void* barbiere_routine(void* arg){
    usleep(1000*1000);
    while(1){
        if(!isEmpty()){
            pthread_mutex_lock(&sediaBarbiere);
            unsigned long cliente = dequeue();
            printf(BLUE "Sto talgiando i capelli al cliente %lu \n", cliente);
            usleep(1000*30*(rand()%100));
            printf(BLUE "Ho finito il taglio del cliente %lu\n", cliente);
            pthread_mutex_unlock(&sediaBarbiere);  
        }
        else{
            pthread_mutex_lock(&sediaBarbiere);  
            printf(GREEN "Mi faccio un pisolino, tanto non ci sono clienti\n");
            while(isEmpty())
                printf("");
            pthread_mutex_unlock(&sediaBarbiere);  
        }
    }
    return NULL;
}

void* prod(){
    while(1){
        pthread_t thread;
        pthread_create(&thread, NULL, cliente, NULL);
        usleep(1000*20*(rand()%100));
    }
    return NULL;
}

int main(){
    printf("Programma che implementa il problema del barbiere addormentato.\n\n");
    sedie.front = -1;
    sedie.rear = -1;
    pthread_t barbiere, produttoreClienti;
    srand(time(NULL));
    pthread_mutex_init(&sediaBarbiere, NULL);
    pthread_mutex_init(&attesa, NULL);

    pthread_create(&barbiere, NULL, barbiere_routine, NULL);
    pthread_create(&produttoreClienti, NULL, prod, NULL);
    pthread_join(barbiere, NULL);
    pthread_join(produttoreClienti, NULL);

    pthread_mutex_destroy(&sediaBarbiere);
    pthread_mutex_destroy(&attesa);

    return 0;
}