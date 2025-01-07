#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 3

int contatoreUno = 0; // Contatore condiviso
int contatoreDue = 0; // Contatore condiviso
pthread_mutex_t mutex; // Mutex per proteggere l'accesso al contatore

void* threadUno(void* arg){
    pthread_mutex_lock(&mutex); // Acquisisce il mutex
    contatoreUno++;
    pthread_mutex_unlock(&mutex); // Rilascia il mutex
    printf("[PID %d] Thread %d\n", getpid(), contatoreUno);
    return NULL;
}

void* threadDue(void* arg){
    pthread_mutex_lock(&mutex); // Acquisisce il mutex
    contatoreDue++;
    sleep(1);
    pthread_mutex_unlock(&mutex); // Rilascia il mutex
    printf("[PID %d] Thread %d\n", getpid(), contatoreDue);
    return NULL;
}


int main() {
    
    printf("Programma che crea N thread sempre per due processi distinti\n\n");

    // fork();

    pthread_t threadsUno[NUM_THREADS];
    pthread_t threadsDue[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL); // Inizializza il mutex

    // Creazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threadsUno[i], NULL, threadUno, NULL);
        pthread_create(&threadsDue[i], NULL, threadDue, NULL);
    }

    // Attesa della terminazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threadsUno[i], NULL);
        pthread_join(threadsDue[i], NULL);
    }

    //printf("Eseguiti %d thread del processo %d\n", contatore, getpid());
    pthread_mutex_destroy(&mutex); // Distrugge il mutex

    return 0;
}
