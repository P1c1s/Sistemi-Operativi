#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include "queue.h"

#define NUMERO_PROCESSI 10
#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
Queue* coda;
int contatoreProcessiCreati;
int numeroProcessiInCoda;
int numeroProcessi;
int processati = 0;
double turnaroundtimes = 0;

void* creazioneProcesso(void* arg){
    pthread_mutex_lock(&mutex2);
    Process* processo = (Process*)malloc(sizeof(Process));
    processo->id = (long) pthread_self();
    gettimeofday(&(processo->arrival), NULL);
    contatoreProcessiCreati++;
    printf("Creato processo n° %d con TID [%ld]\n", contatoreProcessiCreati, processo->id);
    enqueue(coda, processo);
    pthread_mutex_unlock(&mutex2);
    return NULL;
}

void statistiche(){
    printf(RESET "\nStatistiche\n");
    printf(RESET "Totale processi in coda: %d\n", numeroProcessiInCoda);
    printf(RESET "Turnaround time medio: %f\n\n", turnaroundtimes/processati);
}

void* prod(void* arg){
    pthread_t processi[NUMERO_PROCESSI];
    while(1){
        pthread_mutex_lock(&mutex1);
        printf(GREEN "\nProduzione di %d processi per volta.\n", NUMERO_PROCESSI);
        contatoreProcessiCreati = 0;
        for(int i=0; i<NUMERO_PROCESSI; i++)
            pthread_create(&processi[i], NULL, creazioneProcesso, NULL);
        for(int i=0; i<NUMERO_PROCESSI; i++)
            pthread_join(processi[i], NULL);
        numeroProcessiInCoda +=10;
        statistiche();
        pthread_mutex_unlock(&mutex1);
        sleep(1);
    }
    return NULL;
}

void* cons(void* arg){
    Process* processato;
    while(1){
        pthread_mutex_lock(&mutex1);
        if(isQueueEmpty(coda) == 0){
            processato = dequeue(coda);
            gettimeofday(&(processato->start), NULL);
            usleep((rand()%100)*5000);
            gettimeofday(&(processato->end), NULL);
            double tempo = (processato->end.tv_sec - processato->start.tv_sec) + (processato->end.tv_usec - processato->start.tv_usec) / 1000000.0;
            turnaroundtimes += tempo;
            processati++;
            printf(YELLOW "[TID %ld] Processato con tempo: %f\n" RESET, processato->id, tempo);
            numeroProcessiInCoda--;
        }
        pthread_mutex_unlock(&mutex1);
        usleep((rand()%100) *1000);

    }
    return NULL;
}

int main(){
    numeroProcessi = 0;
    system("clear");
    coda = (Queue*)malloc(sizeof(Queue));
    pthread_t produttore;
    pthread_t consumatore;
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);

    srand(time(NULL));
   
    initializeQueue(coda);

    pthread_create(&produttore, NULL, prod, NULL);
    pthread_create(&consumatore, NULL, cons, NULL);

    pthread_join(produttore, NULL);
    pthread_join(consumatore, NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}