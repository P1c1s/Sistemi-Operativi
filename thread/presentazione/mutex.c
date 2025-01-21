#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define RESET   "\033[0m"  // Reset del colore
#define RED     "\033[31m" // Rosso
#define GREEN   "\033[32m" // Verde
#define YELLOW  "\033[33m" // Giallo
#define BLUE    "\033[34m" // Blu
#define MAGENTA "\033[35m" // Magenta
#define CYAN    "\033[36m" // Ciano
#define WHITE   "\033[37m" // Bianco

#define NUM_THREADS 2
int numero;
pthread_mutex_t mutex1;

void* thread(void* arg){
    printf(GREEN "[TID %ld] Inizio a lavorare\n" RESET, pthread_self());
    pthread_mutex_lock(&mutex1);
    printf(RED "Queste quattro stampe ROSSE sono dentro ad una mutex, questo non implica che vengano effettuate sequenzialmente\n", pthread_self());
    printf("[TID %ld] Ho fatto una mutex_lock così da accedere alla risorsa condivisa 'numero'\n", pthread_self());
    numero = rand()%100;
    printf("[TID %ld] %d\n", pthread_self(), numero);
    printf("[TID %ld] Sto per fare una mutex_unlock per rilasciare la risorsa 'numero'\n", pthread_self());
    pthread_mutex_unlock(&mutex1);
    printf(YELLOW "[TID %ld] Ho finito il mio lavoro\n" RESET, pthread_self());
    return NULL;
}

int main(){

    printf("Programma che avvia due threads usando una mutex.\n\n");

    srand(time(NULL));

    pthread_mutex_init(&mutex1, NULL);

    pthread_t threads[NUM_THREADS];

    for(int i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, thread, NULL);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex1);

    return 0;
}