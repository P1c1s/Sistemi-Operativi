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

#define NUM_THREADS 10
int contatoreUno;
int contatoreDue;
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
pthread_mutex_t mutex3;

void* threadEfficente(void* arg){
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pthread_mutex_lock(&mutex1);
    contatoreUno++;
    pthread_mutex_unlock(&mutex1);
    sleep(1);
    pthread_mutex_lock(&mutex2);
    contatoreDue++;
    pthread_mutex_unlock(&mutex2);

    gettimeofday(&end, NULL);
    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf(GREEN "[Eff] Tempo: %2f\n", tempo);
    usleep(1000);
    return NULL;
}

void* threadNonEfficente(void* arg){
    struct timeval start, end;
    gettimeofday(&start, NULL);

    pthread_mutex_lock(&mutex3);
    contatoreUno++;
    sleep(1);
    contatoreDue++;
    pthread_mutex_unlock(&mutex3);

    gettimeofday(&end, NULL);
    double tempo = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    printf(RED "[Non Eff] Tempo: %2f\n", tempo);
    usleep(1000);
    return NULL;
}


int main(){

    printf("Programma che esegue due tipologie di thread svolgono le stesse oprazioni ma in modo diverso\n");
    printf("entrambe aggiornano il valore di due contatori con una sleep(1) in mezzo.\n");
    printf("1. threadEfficente() esegue due mutex distinte distribuendo così il carico di lavoro\n");
    printf("2. threadNonEfficente() esegue una sola mutex aggiornando in modo sequenziale le istruzioni\n\n");

    srand(time(NULL));

    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_mutex_init(&mutex3, NULL);

    pthread_t threadsUno[NUM_THREADS];
    pthread_t threadsDue[NUM_THREADS];

    for(int i=0; i<NUM_THREADS; i++){
        pthread_create(&threadsUno[i], NULL, threadEfficente, NULL);
        pthread_create(&threadsDue[i], NULL, threadNonEfficente, NULL);
    }

    for(int i=0; i<NUM_THREADS; i++){
        pthread_join(threadsUno[i], NULL);
        pthread_join(threadsDue[i], NULL);
    }

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);
    pthread_mutex_destroy(&mutex3);

    return 0;
}