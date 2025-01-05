#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 3

int contatore = 0; // Contatore condiviso
pthread_mutex_t mutex; // Mutex per proteggere l'accesso al contatore

void* creazioneThread(void* arg){
    pthread_mutex_lock(&mutex); // Acquisisce il mutex
    contatore++;
    pthread_mutex_unlock(&mutex); // Rilascia il mutex
    printf("[PID %d] Thread %d\n", getpid(), contatore);
    return NULL;
}

int main() {
    
    printf("Programma che crea N thread sempre per due processi distinti\n\n");

    fork();

    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL); // Inizializza il mutex

    // Creazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, creazioneThread, NULL);
    }

    // Attesa della terminazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Eseguiti %d thread del processo %d\n", contatore, getpid());
    pthread_mutex_destroy(&mutex); // Distrugge il mutex

    return 0;
}
