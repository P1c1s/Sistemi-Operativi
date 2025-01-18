#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>

#define NUM_THREADS 2
#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

pthread_mutex_t mutex;

// Funzione che verrà eseguita dai thread
void* creazioneThread(void* arg) {
    pid_t pid = *((int*)arg); // Cast dell'argomento a un intero
    pthread_t thread_id = lopthread_self(); // Ottiene l'ID del thread corrente
    if(pid>0){
        printf(GREEN "[PID %d] [TID %lu] Sono il genitore e inizo a lavorare\n" RESET, getpid(), (unsigned long)thread_id);
        usleep(10000*(rand()%100));
        for(int i=0; i<3; i++){
            printf(YELLOW "[PID %d] [TID %lu] Sono il genitore e sto lavorando\n" RESET, getpid(), (unsigned long)thread_id);
            usleep(10000*(rand()%100));
        }
        printf(RED "[PID %d] [TID %lu] Sono il genitore finito di lavorare\n" RESET, getpid(), (unsigned long)thread_id);
        usleep(10000*(rand()%100));
    }
    else if(pid==0){
        printf(GREEN "[PID %d] [TID %lu] Sono il figlio e inizo a lavorare\n" RESET, getpid(), (unsigned long)thread_id);
        usleep(10000*(rand()%100));
        for(int i=0; i<3; i++){
            printf(YELLOW "[PID %d] [TID %lu] Sono il figlio e sto lavorando\n" RESET, getpid(), (unsigned long)thread_id);
            usleep(10000*(rand()%100));
        }
        printf(RED "[PID %d] [TID %lu] Sono il figlio finito di lavorare\n" RESET, getpid(), (unsigned long)thread_id);
    }
    return NULL;
}

int main() {

    printf("Programma che crea due processi che sfruttano una funzione\n");
    printf("per creare tre thread ciascuno.\n\n");

    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);

    pid_t pid = fork();
    pthread_t threads[NUM_THREADS]; // Array per memorizzare gli ID dei thread

    // Creazione dei thread
    for(int i=0; i<NUM_THREADS; i++){
        if (pthread_create(&threads[i], NULL, creazioneThread, (void*)&pid) != 0) {
            fprintf(stderr, "Errore creazione thread");
            exit(1);
        }
    }

    // Attesa della terminazione dei thread
    for(int i=0; i<NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}
