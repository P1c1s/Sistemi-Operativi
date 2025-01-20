#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5 // Numero di thread da creare

// Funzione che esegue il lavoro del thread
void* print_message(void* thread_id) {
    long tid = (long)thread_id; // Convertire l'ID del thread
    printf("Ciao dal thread %ld!\n", tid);
    return NULL; // Terminare il thread
}

int main() {
    pthread_t threads[NUM_THREADS]; // Array di thread

    // Creazione dei thread
    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, print_message, (void*)i) != 0) {
            perror("Errore nella creazione del thread");
            exit(EXIT_FAILURE);
        }
    }

    // Attendere la terminazione di ogni thread
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Tutti i thread sono terminati.\n");
    return 0;
}
