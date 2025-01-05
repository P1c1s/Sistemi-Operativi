#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3

// Funzione che verrà eseguita dai thread
void* creazioneThread(void* arg) {
    int pid = *((int*)arg); // Cast dell'argomento a un intero
    pthread_t thread_id = pthread_self(); // Ottiene l'ID del thread corrente
    if(pid>0)
        printf("[PID %d] Processo genitore - Thread ID: %lu\n", getpid(), (unsigned long)thread_id);
    else if(pid==0)
        printf("[PID %d] Processo figlio - Thread ID: %lu\n", getpid(), (unsigned long)thread_id);
    return NULL;
}

int main() {

    printf("Programma che crea due processi che sfruttano una funzione\n");
    printf("per creare tre thread ciasuno\n\n");

    int pid = fork();
    pthread_t threads[NUM_THREADS]; // Array per memorizzare gli ID dei thread

    // Creazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, creazioneThread, (void*)&pid) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Attesa della terminazione dei thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    //printf("Tutti i thread sono terminati.\n");
    return 0;
}
