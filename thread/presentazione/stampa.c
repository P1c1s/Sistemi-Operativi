#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 5

int contatore = 0; // Contatore condiviso
pthread_mutex_t mutex; // Mutex per proteggere l'accesso al contatore

void* creazioneThread(void* arg){
    int* ordineLancio = (int*) arg;
    pthread_mutex_lock(&mutex); // Acquisisce il mutex
    contatore++;
    printf("[PID %d] %d° thread avviato che ha modificato il contatore in comune a %d\n", getpid(), *ordineLancio, contatore);
    pthread_mutex_unlock(&mutex); // Rilascia il mutex
    return NULL;
}

int main() {

    printf("Programma che crea n thread sempre nello stesso processo\n");
    printf("che sfruttano una varibile condivisa come contatore.\n\n");

    int posizioni[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL); // Inizializza il mutex

    // Creazione dei thread
    for(int i=0; i<NUM_THREADS; i++){
        posizioni[i] = i+1;
        pthread_create(&threads[i], NULL, creazioneThread, (void*)&posizioni[i]);
    }

    // Attesa della terminazione dei thread
    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("\nEseguiti %d thread del processo %d\n", contatore, getpid());
    pthread_mutex_destroy(&mutex); // Distrugge il mutex

    return 0;

}
