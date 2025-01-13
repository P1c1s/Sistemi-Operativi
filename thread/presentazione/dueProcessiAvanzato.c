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

// Funzione che verrà eseguita dai thread
void* creazioneThread(void* arg) {
    int genitore = 0;
    int figlio = 0;
    int pid = *((int*)arg); // Cast dell'argomento a un intero
    pthread_t thread_id = pthread_self(); // Ottiene l'ID del thread corrente
    if(pid>0){
        //wait(NULL);
        printf(GREEN "[PID %d] [TID %lu] Sono il genitore e inizo a lavorare\n", getpid(), (unsigned long)thread_id);
        for(int i=0; i<3; i++){
            printf(YELLOW "[PID %d] [TID %lu] Sono il genitore e sto lavorando\n", getpid(), (unsigned long)thread_id);
            for(int j=0; j<1000; j++)
                for(int j=0; j<1000; j++)
                    genitore++;
        }
        printf(RED "[PID %d] [TID %lu] Sono il genitore finito di lavorare\n", getpid(), (unsigned long)thread_id);
    }
    else if(pid==0){
        printf(GREEN "[PID %d] [TID %lu] Sono il figlio e inizo a lavorare\n", getpid(), (unsigned long)thread_id);
        for(int i=0; i<3; i++){
            printf(YELLOW "[PID %d] [TID %lu] Sono il figlio e sto lavorando\n", getpid(), (unsigned long)thread_id);
            for(int j=0; j<1000; j++)
                for(int j=0; j<1000; j++)
                    figlio++;
        }
        printf(RED "[PID %d] [TID %lu] Sono il figlio finito di lavorare\n", getpid(), (unsigned long)thread_id);
    }
    return NULL;
}

int main() {

    printf("Programma che crea due processi che sfruttano una funzione\n");
    printf("per creare tre thread ciascuno.\n\n");

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

    return 0;
}
